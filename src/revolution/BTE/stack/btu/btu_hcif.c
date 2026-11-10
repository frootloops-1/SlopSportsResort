/******************************************************************************
 *
 *  NOTICE OF CHANGES
 *      - Trimmed to the older (Wii) BTE btu_hcif: single controller, no
 *        BLE/AMP/SSP, simplified event handlers.
 *
 *  Compile with REVOLUTION defined to include these changes.
 *
 ******************************************************************************/

/******************************************************************************
 *
 *  Copyright (C) 1999-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

/******************************************************************************
 *
 *  This file contains functions that interface with the HCI transport. On
 *  the receive side, it routes events to the appropriate handler, e.g.
 *  L2CAP, ScoMgr. On the transmit side, it manages the command
 *  transmission.
 *
 ******************************************************************************/

/* Wii (older BTE) structure layouts */
#define BTM_WII_LAYOUT
#define L2C_WII_LAYOUT

/* Wii prototypes that differ from the shared headers */
#define btm_sco_chk_pend_unpark btm_sco_chk_pend_unpark_proto_unused
#define l2c_link_role_changed   l2c_link_role_changed_proto_unused
#define btm_process_inq_complete btm_process_inq_complete_proto_unused

#include <string.h>

#include "gki.h"
#include "bt_types.h"
#include "hcimsgs.h"
#include "btu.h"
#include "l2c_int.h"
#include "btm_api.h"
#include "btm_int.h"
#include "misc.h"

#undef btm_sco_chk_pend_unpark
#undef l2c_link_role_changed
#undef btm_process_inq_complete

extern void btm_sco_chk_pend_unpark (UINT8 hci_status, UINT16 hci_handle, UINT8 mode);
extern void l2c_link_role_changed (BD_ADDR bd_addr, UINT8 new_role);
extern void btm_process_inq_complete (UINT8 status);
extern void hidd_pm_proc_mode_change (UINT8 hci_status, UINT8 mode, UINT16 interval);

/********************************************************************************/
/*              L O C A L    F U N C T I O N     P R O T O T Y P E S            */
/********************************************************************************/
void btu_hcif_connection_comp_evt (UINT8 *p, UINT16 evt_len);
void btu_hcif_connection_request_evt (UINT8 *p, UINT16 evt_len);
void btu_hcif_qos_setup_comp_evt (UINT8 *p, UINT16 evt_len);
void btu_hcif_esco_connection_comp_evt (UINT8 *p, UINT16 evt_len);
void btu_hcif_hdl_command_complete (UINT16 opcode, UINT8 *p, UINT16 evt_len);
void btu_hcif_command_complete_evt (UINT8 *p, UINT16 evt_len);
void btu_hcif_hdl_command_status (UINT16 opcode, UINT8 status, UINT8 *p_cmd);
void btu_hcif_command_status_evt (UINT8 *p, UINT16 evt_len);
void btu_hcif_link_key_notification_evt (UINT8 *p, UINT16 evt_len);

/*******************************************************************************
** Small event handlers (inlined into btu_hcif_process_event)
*******************************************************************************/
static void btu_hcif_inquiry_comp_evt (UINT8 *p, UINT16 evt_len)
{
    UINT8   status;

    STREAM_TO_UINT8 (status, p);

    btm_process_inq_complete(status);
}

static void btu_hcif_inquiry_result_evt (UINT8 *p, UINT16 evt_len)
{
    btm_process_inq_results (p, BTM_INQ_RESULT_STANDARD);
}

static void btu_hcif_inquiry_rssi_result_evt (UINT8 *p, UINT16 evt_len)
{
    btm_process_inq_results (p, BTM_INQ_RESULT_WITH_RSSI);
}

static void btu_hcif_disconnection_comp_evt (UINT8 *p, UINT16 evt_len)
{
    UINT8   status;
    UINT16  handle;
    UINT8   reason;

    STREAM_TO_UINT8  (status, p);
    STREAM_TO_UINT16 (handle, p);
    STREAM_TO_UINT8  (reason, p);

    handle = HCID_GET_HANDLE (handle);

    if (!l2c_link_hci_disc_comp (handle, reason))
    {
        /* If L2CAP doesn't know about it, send it to SCO */
        btm_sco_removed (handle, reason);
    }

    /* Notify security manager */
    btm_sec_disconnected (handle, reason);
}

static void btu_hcif_authentication_comp_evt (UINT8 *p, UINT16 evt_len)
{
    UINT8   status;
    UINT16  handle;

    STREAM_TO_UINT8  (status, p);
    STREAM_TO_UINT16 (handle, p);

    btm_sec_auth_complete (handle, status);
}

static void btu_hcif_rmt_name_request_comp_evt (UINT8 *p, UINT16 evt_len)
{
    UINT8   status;
    BD_ADDR bd_addr;

    STREAM_TO_UINT8 (status, p);
    STREAM_TO_BDADDR (bd_addr, p);

    evt_len -= (1 + BD_ADDR_LEN);

    btm_process_remote_name (bd_addr, p, evt_len, status);

    btm_sec_rmt_name_request_complete (bd_addr, p, status);
}

static void btu_hcif_encryption_change_evt (UINT8 *p, UINT16 evt_len)
{
    UINT8   status;
    UINT16  handle;
    UINT8   encr_enable;

    STREAM_TO_UINT8  (status, p);
    STREAM_TO_UINT16 (handle, p);
    STREAM_TO_UINT8  (encr_enable, p);

    btm_acl_encrypt_change (handle, status, encr_enable);
    btm_sec_encrypt_change (handle, status, encr_enable);
}

static void btu_hcif_master_link_key_comp_evt (UINT8 *p, UINT16 evt_len)
{
    UINT8   status;
    UINT16  handle;
    UINT8   key_flg;

    STREAM_TO_UINT8  (status, p);
    STREAM_TO_UINT16 (handle, p);
    STREAM_TO_UINT8  (key_flg, p);

    btm_sec_mkey_comp_event (handle, status, key_flg);
}

static void btu_hcif_read_rmt_features_comp_evt (UINT8 *p, UINT16 evt_len)
{
    btm_read_remote_features_complete(p);
}

static void btu_hcif_read_rmt_version_comp_evt (UINT8 *p, UINT16 evt_len)
{
    btm_read_remote_version_complete (p);
}

static void btu_hcif_hardware_error_evt (UINT8 *p, UINT16 evt_len)
{
    BT_TRACE_0 (TRACE_LAYER_HCI, TRACE_TYPE_ERROR, "Ctlr H/w error event");

    /* Reset the controller */
    if (BTM_IsDeviceUp())
        BTM_DeviceReset (NULL);
}

static void btu_hcif_role_change_evt (UINT8 *p, UINT16 evt_len)
{
    UINT8       status;
    BD_ADDR     bda;
    UINT8       role;

    STREAM_TO_UINT8 (status, p);
    STREAM_TO_BDADDR (bda, p);
    STREAM_TO_UINT8  (role, p);

    if (status == HCI_SUCCESS)
        l2c_link_role_changed (bda, role);

    btm_acl_role_changed(status, bda, role);
}

static void btu_hcif_num_compl_data_pkts_evt (UINT8 *p, UINT16 evt_len)
{
    /* Process for L2CAP and SCO */
    l2c_link_process_num_completed_pkts (p);
}

static void btu_hcif_mode_change_evt (UINT8 *p, UINT16 evt_len)
{
    UINT8       status;
    UINT16      handle;
    UINT8       current_mode;
    UINT16      interval;

    STREAM_TO_UINT8 (status, p);

    STREAM_TO_UINT16 (handle, p);
    STREAM_TO_UINT8 (current_mode, p);
    STREAM_TO_UINT16 (interval, p);
    btm_sco_chk_pend_unpark (status, handle, current_mode);
    btm_pm_proc_mode_change (status, handle, current_mode, interval);
    hidd_pm_proc_mode_change (status, current_mode, interval);
}

static void btu_hcif_return_link_keys_evt (UINT8 *p, UINT16 evt_len)
{
    UINT8                       num_keys;
    tBTM_RETURN_LINK_KEYS_EVT   *result;

    /* get the number of link keys */
    num_keys = *p;

    /* If there are no link keys don't call the call back */
    if (!num_keys)
        return;

    /* Take one extra byte at the beginning to specify event */
    result = (tBTM_RETURN_LINK_KEYS_EVT *)(--p);
    result->event = BTM_CB_EVT_RETURN_LINK_KEYS;

    /* Call the BTM function to pass the link keys to application */
    btm_return_link_keys_evt (result);
}

static void btu_hcif_pin_code_request_evt (UINT8 *p, UINT16 evt_len)
{
    BD_ADDR  bda;

    STREAM_TO_BDADDR (bda, p);

    /* Tell L2CAP that there was a PIN code request,  */
    /* it may need to stretch timeouts                */
    l2c_pin_code_request (bda);

    btm_sec_pin_code_request (bda);
}

static void btu_hcif_link_key_request_evt (UINT8 *p, UINT16 evt_len)
{
    BD_ADDR  bda;

    STREAM_TO_BDADDR (bda, p);
    btm_sec_link_key_request (bda);
}

static void btu_hcif_read_clock_off_comp_evt (UINT8 *p, UINT16 evt_len)
{
    UINT8       status;
    UINT16      handle;
    UINT16      clock_offset;

    STREAM_TO_UINT8  (status, p);

    /* If failed to get clock offset just drop the result */
    if (status != HCI_SUCCESS)
        return;

    STREAM_TO_UINT16 (handle, p);
    STREAM_TO_UINT16 (clock_offset, p);

    handle = HCID_GET_HANDLE (handle);

    btm_process_clk_off_comp_evt (handle, clock_offset);
    btm_sec_update_clock_offset (handle, clock_offset);
}

static void btu_hcif_qos_violation_evt (UINT8 *p, UINT16 evt_len)
{
    UINT16   handle;

    STREAM_TO_UINT16 (handle, p);

    handle = HCID_GET_HANDLE (handle);

    l2c_link_hci_qos_violation (handle);
}

static void btu_hcif_esco_connection_chg_evt (UINT8 *p, UINT16 evt_len)
{
    UINT16  handle;
    UINT16  tx_pkt_len;
    UINT16  rx_pkt_len;
    UINT8   status;
    UINT8   tx_interval;
    UINT8   retrans_window;

    STREAM_TO_UINT8 (status, p);
    STREAM_TO_UINT16 (handle, p);

    STREAM_TO_UINT8 (tx_interval, p);
    STREAM_TO_UINT8 (retrans_window, p);
    STREAM_TO_UINT16 (rx_pkt_len, p);
    STREAM_TO_UINT16 (tx_pkt_len, p);

    btm_esco_proc_conn_chg (status, handle, tx_interval, retrans_window,
                            rx_pkt_len, tx_pkt_len);
}

/*******************************************************************************
**
** Function         btu_hcif_store_cmd
**
** Description      This function stores a copy of an outgoing command and
**                  and sets a timer waiting for a event in response to the
**                  command.
**
** Returns          void
**
*******************************************************************************/
static void btu_hcif_store_cmd (BT_HDR *p_buf)
{
    UINT16  opcode;
    BT_HDR  *p_cmd;
    UINT8   *p = (UINT8 *)(p_buf + 1) + p_buf->offset;

    /* get command opcode */
    STREAM_TO_UINT16 (opcode, p);

    /* don't do anything for certain commands */
    if ((opcode == HCI_RESET) || (opcode == HCI_HOST_NUM_PACKETS_DONE))
    {
        return;
    }

    /* allocate buffer */
    if ((p_cmd = (BT_HDR *) GKI_getpoolbuf (HCI_CMD_POOL_ID)) == NULL)
    {
        return;
    }

    /* copy buffer */
    memcpy (p_cmd, p_buf, sizeof(BT_HDR));

    memcpy ((UINT8 *)(p_cmd + 1) + p_cmd->offset,
            (UINT8 *)(p_buf + 1) + p_buf->offset, p_buf->len);

    /* queue copy of cmd */
    GKI_enqueue(&(btu_cb.cmd_cmpl_q), p_cmd);

    /* start timer */
    btu_start_timer (&(btu_cb.cmd_cmpl_timer), BTU_TTYPE_BTU_CMD_CMPL,
                     BTU_CMD_CMPL_TIMEOUT);
}

/*******************************************************************************
**
** Function         btu_hcif_process_event
**
** Description      This function is called when an event is received from
**                  the Host Controller.
**
** Returns          void
**
*******************************************************************************/
void btu_hcif_process_event (BT_HDR *p_msg)
{
    UINT8   *p = (UINT8 *)(p_msg + 1) + p_msg->offset;
    UINT8   hci_evt_code, hci_evt_len;

    STREAM_TO_UINT8  (hci_evt_code, p);
    STREAM_TO_UINT8  (hci_evt_len, p);

    /* Before the reset completes, only command complete/status are handled */
    if ((btm_cb.devcb.state == BTM_DEV_STATE_WAIT_RESET_CMPLT)
     && (hci_evt_code != HCI_COMMAND_COMPLETE_EVT)
     && (hci_evt_code != HCI_COMMAND_STATUS_EVT))
        return;

    switch (hci_evt_code)
    {
        case HCI_INQUIRY_COMP_EVT:
            btu_hcif_inquiry_comp_evt (p, hci_evt_len);
            break;
        case HCI_INQUIRY_RESULT_EVT:
            btu_hcif_inquiry_result_evt (p, hci_evt_len);
            break;
        case HCI_INQUIRY_RSSI_RESULT_EVT:
            btu_hcif_inquiry_rssi_result_evt (p, hci_evt_len);
            break;
        case HCI_CONNECTION_COMP_EVT:
            btu_hcif_connection_comp_evt (p, hci_evt_len);
            break;
        case HCI_CONNECTION_REQUEST_EVT:
            btu_hcif_connection_request_evt (p, hci_evt_len);
            break;
        case HCI_DISCONNECTION_COMP_EVT:
            btu_hcif_disconnection_comp_evt (p, hci_evt_len);
            break;
        case HCI_AUTHENTICATION_COMP_EVT:
            btu_hcif_authentication_comp_evt (p, hci_evt_len);
            break;
        case HCI_RMT_NAME_REQUEST_COMP_EVT:
            btu_hcif_rmt_name_request_comp_evt (p, hci_evt_len);
            break;
        case HCI_ENCRYPTION_CHANGE_EVT:
            btu_hcif_encryption_change_evt (p, hci_evt_len);
            break;
        case HCI_MASTER_LINK_KEY_COMP_EVT:
            btu_hcif_master_link_key_comp_evt (p, hci_evt_len);
            break;
        case HCI_READ_RMT_FEATURES_COMP_EVT:
            btu_hcif_read_rmt_features_comp_evt (p, hci_evt_len);
            break;
        case HCI_READ_RMT_VERSION_COMP_EVT:
            btu_hcif_read_rmt_version_comp_evt (p, hci_evt_len);
            break;
        case HCI_QOS_SETUP_COMP_EVT:
            btu_hcif_qos_setup_comp_evt (p, hci_evt_len);
            break;
        case HCI_COMMAND_COMPLETE_EVT:
            btu_hcif_command_complete_evt (p, hci_evt_len);
            break;
        case HCI_COMMAND_STATUS_EVT:
            btu_hcif_command_status_evt (p, hci_evt_len);
            break;
        case HCI_HARDWARE_ERROR_EVT:
            btu_hcif_hardware_error_evt (p, hci_evt_len);
            break;
        case HCI_ROLE_CHANGE_EVT:
            btu_hcif_role_change_evt (p, hci_evt_len);
            break;
        case HCI_NUM_COMPL_DATA_PKTS_EVT:
            btu_hcif_num_compl_data_pkts_evt (p, hci_evt_len);
            break;
        case HCI_MODE_CHANGE_EVT:
            btu_hcif_mode_change_evt (p, hci_evt_len);
            break;
        case HCI_RETURN_LINK_KEYS_EVT:
            btu_hcif_return_link_keys_evt (p, hci_evt_len);
            break;
        case HCI_PIN_CODE_REQUEST_EVT:
            btu_hcif_pin_code_request_evt (p, hci_evt_len);
            break;
        case HCI_LINK_KEY_REQUEST_EVT:
            btu_hcif_link_key_request_evt (p, hci_evt_len);
            break;
        case HCI_LINK_KEY_NOTIFICATION_EVT:
            btu_hcif_link_key_notification_evt (p, hci_evt_len);
            break;
        case HCI_READ_CLOCK_OFF_COMP_EVT:
            btu_hcif_read_clock_off_comp_evt (p, hci_evt_len);
            break;
        case HCI_QOS_VIOLATION_EVT:
            btu_hcif_qos_violation_evt (p, hci_evt_len);
            break;
        case HCI_FLOW_SPECIFICATION_COMP_EVT:
            break;
        case HCI_ESCO_CONNECTION_COMP_EVT:
            btu_hcif_esco_connection_comp_evt (p, hci_evt_len);
            break;
        case HCI_ESCO_CONNECTION_CHANGED_EVT:
            btu_hcif_esco_connection_chg_evt (p, hci_evt_len);
            break;
        case 0xEF:
        case HCI_VENDOR_SPECIFIC_EVT:
            btm_vendor_specific_evt (p, hci_evt_len);
            break;
    }
}


/*******************************************************************************
**
** Function         btu_hcif_send_cmd
**
** Description      This function is called to check if it can send commands
**                  to the Host Controller. It may be passed the address of
**                  a packet to send.
**
** Returns          void
**
*******************************************************************************/
void btu_hcif_send_cmd (BT_HDR *p_buf)
{
    /* If there are already commands in the queue, then enqueue this command */
    if ((p_buf) && (btu_cb.cmd_xmit_q.count))
    {
        GKI_enqueue (&(btu_cb.cmd_xmit_q), p_buf);
        p_buf = NULL;
    }

    /* Allow for startup case, where no acks may be received */
    if ((btu_cb.controller_cmd_window == 0)
     && (btm_cb.devcb.state == BTM_DEV_STATE_WAIT_RESET_CMPLT))
    {
        btu_cb.controller_cmd_window = btu_cb.cmd_xmit_q.count + 1;
    }

    /* See if we can send anything */
    while (btu_cb.controller_cmd_window != 0)
    {
        if (!p_buf)
            p_buf = (BT_HDR *)GKI_dequeue (&(btu_cb.cmd_xmit_q));

        if (p_buf)
        {
            btu_hcif_store_cmd(p_buf);

            btu_cb.controller_cmd_window--;

            bte_hcisu_send ((HC_BT_HDR *)p_buf, BT_EVT_TO_LM_HCI_CMD);

            p_buf = NULL;
        }
        else
            break;
    }

    if (p_buf)
        GKI_enqueue (&(btu_cb.cmd_xmit_q), p_buf);
}


/*******************************************************************************
**
** Function         btu_hcif_connection_comp_evt
**
** Description      Process event HCI_CONN_COMPLETE_EVT
**
** Returns          void
**
*******************************************************************************/
void btu_hcif_connection_comp_evt (UINT8 *p, UINT16 evt_len)
{
    UINT8       status;
    UINT16      handle;
    BD_ADDR     bda;
    UINT8       link_type;
    UINT8       enc_mode;
    tBTM_ESCO_DATA  esco_data;

    STREAM_TO_UINT8    (status, p);
    STREAM_TO_UINT16   (handle, p);
    STREAM_TO_BDADDR   (bda, p);
    STREAM_TO_UINT8    (link_type, p);
    STREAM_TO_UINT8    (enc_mode, p);

    handle = HCID_GET_HANDLE (handle);

    if (link_type == HCI_LINK_TYPE_ACL)
    {
        btm_sec_connected (bda, handle, status, enc_mode);

        l2c_link_hci_conn_comp (status, handle, bda);
    }
    else
    {
        memset(&esco_data, 0, sizeof(tBTM_ESCO_DATA));
        /* esco_data.link_type = HCI_LINK_TYPE_SCO; already zero */
        memcpy (esco_data.bd_addr, bda, BD_ADDR_LEN);
        btm_sco_connected (status, bda, handle, &esco_data);
    }
}


/*******************************************************************************
**
** Function         btu_hcif_connection_request_evt
**
** Description      Process event HCI_CONN_REQUEST_EVT
**
** Returns          void
**
*******************************************************************************/
void btu_hcif_connection_request_evt (UINT8 *p, UINT16 evt_len)
{
    BD_ADDR     bda;
    DEV_CLASS   dc;
    UINT8       link_type;

    STREAM_TO_BDADDR   (bda, p);
    STREAM_TO_DEVCLASS (dc, p);
    STREAM_TO_UINT8    (link_type, p);

    /* Pass request to security manager to check connect filters before */
    /* passing request to l2cap */
    if (link_type == HCI_LINK_TYPE_ACL)
    {
        btm_sec_conn_req (bda, dc);
    }
    else
    {
        btm_sco_conn_req (bda, dc, link_type);
    }
}


/*******************************************************************************
**
** Function         btu_hcif_qos_setup_comp_evt
**
** Description      Process event HCI_QOS_SETUP_COMP_EVT
**
** Returns          void
**
*******************************************************************************/
void btu_hcif_qos_setup_comp_evt (UINT8 *p, UINT16 evt_len)
{
    UINT8 status;
    UINT16 handle;
    FLOW_SPEC flow;

    STREAM_TO_UINT8 (status, p);
    STREAM_TO_UINT16 (handle, p);
    STREAM_TO_UINT8 (flow.qos_flags, p);
    STREAM_TO_UINT8 (flow.service_type, p);
    STREAM_TO_UINT32 (flow.token_rate, p);
    STREAM_TO_UINT32 (flow.peak_bandwidth, p);
    STREAM_TO_UINT32 (flow.latency, p);
    STREAM_TO_UINT32 (flow.delay_variation, p);

    btm_qos_setup_complete(status, handle, &flow);
}


/*******************************************************************************
**
** Function         btu_hcif_esco_connection_comp_evt
**
** Description      Process event HCI_ESCO_CONNECTION_COMP_EVT
**
** Returns          void
**
*******************************************************************************/
void btu_hcif_esco_connection_comp_evt (UINT8 *p, UINT16 evt_len)
{
    tBTM_ESCO_DATA  data;
    UINT16          handle;
    BD_ADDR         bda;
    UINT8           status;

    STREAM_TO_UINT8 (status, p);
    STREAM_TO_UINT16 (handle, p);
    STREAM_TO_BDADDR (bda, p);

    STREAM_TO_UINT8 (data.link_type, p);
    STREAM_TO_UINT8 (data.tx_interval, p);
    STREAM_TO_UINT8 (data.retrans_window, p);
    STREAM_TO_UINT16 (data.rx_pkt_len, p);
    STREAM_TO_UINT16 (data.tx_pkt_len, p);
    STREAM_TO_UINT8 (data.air_mode, p);

    memcpy (data.bd_addr, bda, BD_ADDR_LEN);
    btm_sco_connected (status, bda, handle, &data);
}


/*******************************************************************************
**
** Function         btu_hcif_hdl_command_complete
**
** Description      Handle command complete event
**
** Returns          void
**
*******************************************************************************/
void btu_hcif_hdl_command_complete (UINT16 opcode, UINT8 *p, UINT16 evt_len)
{
    switch (opcode)
    {
        case HCI_RESET:
            btm_reset_complete ();  /* BR/EDR */
            break;

        case HCI_INQUIRY_CANCEL:
            /* Tell inquiry processing that we are done */
            btm_process_inq_complete(HCI_SUCCESS);
            break;
        case HCI_SET_EVENT_FILTER:
            btm_event_filter_complete (p);
            break;

        case HCI_READ_STORED_LINK_KEY:
            btm_read_stored_link_key_complete (p);
            break;

        case HCI_WRITE_STORED_LINK_KEY:
            btm_write_stored_link_key_complete (p);
            break;

        case HCI_DELETE_STORED_LINK_KEY:
            btm_delete_stored_link_key_complete (p);
            break;

        case HCI_READ_LOCAL_VERSION_INFO:
            btm_read_local_version_complete (p, evt_len);
            break;

        case HCI_READ_POLICY_SETTINGS:
            btm_read_link_policy_complete (p);
            break;

        case HCI_READ_BUFFER_SIZE:
            btm_read_hci_buf_size_complete (p, evt_len);
            break;

        case HCI_READ_LOCAL_FEATURES:
            btm_read_local_features_complete (p, evt_len);
            break;

        case HCI_READ_LOCAL_NAME:
            btm_read_local_name_complete (p, evt_len);
            break;

        case HCI_READ_BD_ADDR:
            btm_read_local_addr_complete (p, evt_len);
            break;

        case HCI_GET_LINK_QUALITY:
            btm_read_link_quality_complete (p);
            break;

        case HCI_READ_RSSI:
            btm_read_rssi_complete (p);
            break;

        default:
            if ((opcode & HCI_GRP_VENDOR_SPECIFIC) == HCI_GRP_VENDOR_SPECIFIC)
                btm_vsc_complete (p, opcode, evt_len);
            break;
    }
}

/*******************************************************************************
**
** Function         btu_hcif_command_complete_evt
**
** Description      Process event HCI_COMMAND_COMPLETE_EVT
**
** Returns          void
**
*******************************************************************************/
void btu_hcif_command_complete_evt (UINT8 *p, UINT16 evt_len)
{
    UINT16      cc_opcode;
    BT_HDR      *p_cmd;
    UINT8       *p_data;
    UINT16      cmd_opcode;

    STREAM_TO_UINT8  (btu_cb.controller_cmd_window, p);
    STREAM_TO_UINT16 (cc_opcode, p);

    evt_len -= 3;

    if ((cc_opcode != HCI_RESET) && (cc_opcode != HCI_HOST_NUM_PACKETS_DONE)
     && (cc_opcode != HCI_COMMAND_NONE))
    {
        p_cmd = (BT_HDR *) GKI_dequeue (&btu_cb.cmd_cmpl_q);
        if (p_cmd != NULL)
        {
            p_data = (UINT8 *)(p_cmd + 1);
            STREAM_TO_UINT16 (cmd_opcode, p_data);

            if ((cc_opcode == 0xFC4C) && (cmd_opcode != cc_opcode))
            {
                GKI_enqueue_head (&btu_cb.cmd_cmpl_q, p_cmd);
                return;
            }

            GKI_freebuf (p_cmd);
        }

        if (!GKI_queue_is_empty (&btu_cb.cmd_cmpl_q))
            btu_start_timer (&btu_cb.cmd_cmpl_timer, BTU_TTYPE_BTU_CMD_CMPL,
                             BTU_CMD_CMPL_TIMEOUT);
        else
            btu_stop_timer (&btu_cb.cmd_cmpl_timer);
    }

    btu_hcif_hdl_command_complete (cc_opcode, p, evt_len);

    /* See if we can forward any more commands */
    btu_hcif_send_cmd (NULL);
}


/*******************************************************************************
**
** Function         btu_hcif_hdl_command_status
**
** Description      Handle a command status event
**
** Returns          void
**
*******************************************************************************/
void btu_hcif_hdl_command_status (UINT16 opcode, UINT8 status, UINT8 *p_cmd)
{
    BD_ADDR         bd_addr;
    UINT16          handle;
    tBTM_ESCO_DATA  esco_data;

    switch (opcode)
    {
        case HCI_EXIT_SNIFF_MODE:
        case HCI_EXIT_PARK_MODE:
        case HCI_HOLD_MODE:
        case HCI_SNIFF_MODE:
        case HCI_PARK_MODE:
            btm_pm_proc_cmd_status(status);
            break;

        default:
            /* If command failed to start, we may need to tell BTM */
            if (status != HCI_SUCCESS)
            {
                switch (opcode)
                {
                    case HCI_INQUIRY:
                        /* Tell inquiry processing that we are done */
                        btm_process_inq_complete(status);
                        break;

                    case HCI_RMT_NAME_REQUEST:
                        /* Tell inquiry processing that we are done */
                        btm_process_remote_name (NULL, NULL, 0, status);

                        btm_sec_rmt_name_request_complete (NULL, NULL, status);
                        break;

                    case HCI_QOS_SETUP_COMP_EVT:
                        /* Tell qos setup that we are done */
                        btm_qos_setup_complete(status,0,NULL);
                        break;

                    case HCI_SWITCH_ROLE:
                        /* Tell BTM that the command failed */
                        btm_acl_role_changed(status, NULL, BTM_ROLE_UNDEFINED);
                        l2c_link_role_change_failed ();
                        break;

                    case HCI_CREATE_CONNECTION:
                        /* read bd addr out of stored command */
                        if (p_cmd != NULL)
                        {
                            p_cmd++;
                            STREAM_TO_BDADDR (bd_addr, p_cmd);
                            btm_sec_connected (bd_addr, HCI_INVALID_HANDLE, status, 0);
                            l2c_link_hci_conn_comp (status, HCI_INVALID_HANDLE, bd_addr);
                        }
                        break;

                    case HCI_SETUP_ESCO_CONNECTION:
                        /* read handle out of stored command */
                        if (p_cmd != NULL)
                        {
                            p_cmd++;
                            STREAM_TO_UINT16 (handle, p_cmd);

                            /* Determine if initial connection failed or is a change of setup */
                            if (btm_is_sco_active(handle))
                                btm_esco_proc_conn_chg (status, handle, 0, 0, 0, 0);
                            else
                                btm_sco_connected (status, NULL, handle, &esco_data);
                        }
                        break;

                    default:
                        if ((opcode & HCI_GRP_VENDOR_SPECIFIC) == HCI_GRP_VENDOR_SPECIFIC)
                            btm_vsc_complete (p_cmd, opcode, 1);
                        break;
                }
            }
            break;
    }
}

/*******************************************************************************
**
** Function         btu_hcif_command_status_evt
**
** Description      Process event HCI_COMMAND_STATUS_EVT
**
** Returns          void
**
*******************************************************************************/
void btu_hcif_command_status_evt (UINT8 *p, UINT16 evt_len)
{
    UINT8       status;
    UINT16      opcode;
    UINT16      cmd_opcode;
    BT_HDR      *p_cmd = NULL;
    UINT8       *p_data = NULL;

    STREAM_TO_UINT8  (status, p);
    STREAM_TO_UINT8  (btu_cb.controller_cmd_window, p);
    STREAM_TO_UINT16 (opcode, p);

    /* Ignore command status for these commands */
    if ((opcode != HCI_RESET) && (opcode != HCI_HOST_NUM_PACKETS_DONE)
     && (opcode != HCI_COMMAND_NONE))
    {
        if ((p_cmd = (BT_HDR *) GKI_dequeue (&btu_cb.cmd_cmpl_q)) != NULL)
        {
            p_data = (UINT8 *)(p_cmd + 1) + p_cmd->offset;
            STREAM_TO_UINT16 (cmd_opcode, p_data);

            if (cmd_opcode != opcode)
            {
                p_data = NULL;
                BT_TRACE_2 (TRACE_LAYER_HCI, TRACE_TYPE_WARNING,
                            "Event mismatch opcode=%X cmd opcode=%X", opcode, cmd_opcode);
            }
        }

        /* restart the timer if there are commands left */
        if (!GKI_queue_is_empty (&btu_cb.cmd_cmpl_q))
            btu_start_timer (&btu_cb.cmd_cmpl_timer, BTU_TTYPE_BTU_CMD_CMPL,
                             BTU_CMD_CMPL_TIMEOUT);
        else
            btu_stop_timer (&btu_cb.cmd_cmpl_timer);
    }

    btu_hcif_hdl_command_status (opcode, status, p_data);

    if (p_cmd)
        GKI_freebuf (p_cmd);

    /* See if we can forward any more commands */
    btu_hcif_send_cmd (NULL);
}

/*******************************************************************************
**
** Function         btu_hcif_cmd_timeout
**
** Description      Handle a command timeout
**
** Returns          void
**
*******************************************************************************/
void btu_hcif_cmd_timeout (void)
{
    BT_HDR  *p_cmd;
    UINT8   *p;
    UINT16  opcode;
    UINT8   status;

    /* set the controller cmd window to 1, as if we received a response */
    btu_cb.controller_cmd_window = 1;

    /* get queued command */
    if ((p_cmd = (BT_HDR *) GKI_dequeue (&btu_cb.cmd_cmpl_q)) == NULL)
    {
        BT_TRACE_0 (TRACE_LAYER_HCI, TRACE_TYPE_WARNING, "Cmd timeout; no cmd in queue");
        return;
    }

    /* if more commands in queue restart timer */
    if (!GKI_queue_is_empty (&btu_cb.cmd_cmpl_q))
    {
        btu_start_timer (&btu_cb.cmd_cmpl_timer, BTU_TTYPE_BTU_CMD_CMPL,
                         BTU_CMD_CMPL_TIMEOUT);
    }

    p = (UINT8 *)(p_cmd + 1) + p_cmd->offset;

    /* get opcode from stored command */
    STREAM_TO_UINT16 (opcode, p);

    BT_TRACE_1 (TRACE_LAYER_HCI, TRACE_TYPE_WARNING,
                "BTU HCI command timeout - cmd opcode = 0x%02x", opcode);

    /* send stored command to command status or command complete handler */
    switch (opcode)
    {
        case HCI_INQUIRY:
        case HCI_RMT_NAME_REQUEST:
        case HCI_QOS_SETUP_COMP_EVT:
        case HCI_CREATE_CONNECTION:
        case HCI_HOLD_MODE:
        case HCI_SNIFF_MODE:
        case HCI_EXIT_SNIFF_MODE:
        case HCI_PARK_MODE:
        case HCI_EXIT_PARK_MODE:
            btu_hcif_hdl_command_status (opcode, HCI_ERR_UNSPECIFIED, p);
            break;

        default:
            status = HCI_ERR_UNSPECIFIED;
            btu_hcif_hdl_command_complete (opcode, &status, 1);
            break;
    }

    /* free stored command */
    GKI_freebuf(p_cmd);

    /* If anyone wants device status notifications, give him one */
    btm_report_device_status (BTM_DEV_STATUS_CMD_TOUT);

    /* See if we can forward any more commands */
    btu_hcif_send_cmd (NULL);
}

/*******************************************************************************
**
** Function         btu_hcif_link_key_notification_evt
**
** Description      Process event HCI_LINK_KEY_NOTIFICATION_EVT
**
** Returns          void
**
*******************************************************************************/
void btu_hcif_link_key_notification_evt (UINT8 *p, UINT16 evt_len)
{
    BD_ADDR  bda;
    LINK_KEY key;
    UINT8    key_type;

    STREAM_TO_BDADDR (bda, p);
    STREAM_TO_ARRAY16 (key, p);
    STREAM_TO_UINT8 (key_type, p);

    btm_sec_link_key_notification (bda, key, key_type);
}
