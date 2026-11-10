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
 *  This file contains the main L2CAP entry points
 *
 ******************************************************************************/

/* Wii (older BTE) structure layouts in l2c_int.h */
#define BTM_WII_LAYOUT
#define L2C_WII_LAYOUT

#include "bt_target.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "gki.h"
#include "hcimsgs.h"
#include "l2cdefs.h"
#include "l2c_int.h"
#include "l2c_api.h"
#include "btu.h"
#include "btm_int.h"

/********************************************************************************/
/*              L O C A L    F U N C T I O N     P R O T O T Y P E S            */
/********************************************************************************/
void process_l2cap_cmd (tL2C_LCB *p_lcb, UINT8 *p, UINT16 pkt_len);
extern BOOLEAN btm_sec_is_bonding (UINT16 handle);

/*******************************************************************************
**
** Function         l2c_init
**
** Description      This function is called once at startup to initialize
**                  all the L2CAP structures
**
** Returns          void
**
*******************************************************************************/
void l2c_init (void)
{
    INT16  xx;

    memset (&l2cb, 0, sizeof (tL2C_CB));

    /* Put all the channel control blocks on the free queue */
    for (xx = 0; xx < MAX_L2CAP_CHANNELS - 1; xx++)
    {
        l2cb.ccb_pool[xx].p_next_ccb = &l2cb.ccb_pool[xx + 1];
    }

    l2cb.p_free_ccb_first = &l2cb.ccb_pool[0];
    l2cb.p_free_ccb_last  = &l2cb.ccb_pool[MAX_L2CAP_CHANNELS - 1];

    l2cb.desire_role      = L2CAP_DESIRED_LINK_ROLE;

    /* Set the default idle timeout */
    l2cb.idle_timeout = L2CAP_LINK_INACTIVITY_TOUT;

    l2cb.l2cap_trace_level = BT_TRACE_LEVEL_NONE;    /* No traces */
}

/*******************************************************************************
**
** Function         l2c_rcv_acl_data
**
** Description      This function is called from the HCI Interface when an ACL
**                  data packet is received.
**
** Returns          void
**
*******************************************************************************/
void l2c_rcv_acl_data (BT_HDR *p_msg)
{
    UINT8       *p = (UINT8 *)(p_msg + 1) + p_msg->offset;
    UINT16      handle, hci_len;
    UINT8       pkt_type;
    tL2C_LCB    *p_lcb;
    tL2C_CCB    *p_ccb = NULL;
    UINT16      l2cap_len, rcv_cid, psm;

    /* Extract the handle */
    STREAM_TO_UINT16 (handle, p);
    pkt_type = HCID_GET_EVENT (handle);
    handle   = HCID_GET_HANDLE (handle);

    /* Since the HCI Transport is putting segmented packets back together, we */
    /* should never get a valid packet with the type set to "continuation"    */
    if (pkt_type != L2CAP_PKT_START)
    {
        L2CAP_TRACE_WARNING1 ("L2CAP - expected pkt start, got: %d", pkt_type);
        GKI_freebuf (p_msg);
        return;
    }

    /* Find the LCB based on the handle */
    if ((p_lcb = l2cu_find_lcb_by_handle (handle)) == NULL)
    {
        UINT8       cmd_code;

        /* There is a slight possibility (specifically with USB) that we get an */
        /* L2CAP connection request before we get the HCI connection complete.  */
        /* So for these types of messages, hold them for up to 2 seconds.       */
        STREAM_TO_UINT16 (hci_len, p);
        STREAM_TO_UINT16 (l2cap_len, p);
        STREAM_TO_UINT16 (rcv_cid, p);
        STREAM_TO_UINT8  (cmd_code, p);

        if ((p_msg->layer_specific == 0) && (rcv_cid == L2CAP_SIGNALLING_CID)
            && (cmd_code == L2CAP_CMD_INFO_REQ || cmd_code == L2CAP_CMD_CONN_REQ)
            && (!btm_sec_is_bonding (handle)))
        {
            L2CAP_TRACE_WARNING5 ("L2CAP - holding ACL for unknown handle:%d ls:%d cid:%d opcode:%d cur count:%d",
                                handle, p_msg->layer_specific, rcv_cid, cmd_code,
                                l2cb.rcv_hold_q.count);
            p_msg->layer_specific = 2;
            GKI_enqueue (&l2cb.rcv_hold_q, p_msg);

            if (l2cb.rcv_hold_q.count == 1)
                btu_start_timer (&l2cb.rcv_hold_tle, BTU_TTYPE_L2CAP_HOLD, BT_1SEC_TIMEOUT);

            return;
        }
        GKI_freebuf (p_msg);
        return;
    }

    /* Extract the length and update the buffer header */
    STREAM_TO_UINT16 (hci_len, p);
    p_msg->offset += 4;

    /* Extract the length and CID */
    STREAM_TO_UINT16 (l2cap_len, p);
    STREAM_TO_UINT16 (rcv_cid, p);

    /* Find the CCB for this CID */
    if (rcv_cid > L2CAP_CONNECTIONLESS_CID)
    {
        if ((p_ccb = l2cu_find_ccb_by_cid (p_lcb, rcv_cid)) == NULL)
        {
            L2CAP_TRACE_WARNING1 ("L2CAP - unknown CID: %d", rcv_cid);
            GKI_freebuf (p_msg);
            return;
        }
    }

    if (hci_len >= L2CAP_PKT_OVERHEAD)  /* Must receive at least the L2CAP length and CID.*/
    {
        p_msg->len    = hci_len - L2CAP_PKT_OVERHEAD;
        p_msg->offset += L2CAP_PKT_OVERHEAD;
    }
    else
    {
        L2CAP_TRACE_WARNING0 ("L2CAP - got incorrect hci header" );
        GKI_freebuf (p_msg);
        return;
    }

    if (l2cap_len != p_msg->len)
    {
        L2CAP_TRACE_WARNING2 ("L2CAP - bad length in pkt. Exp: %d  Act: %d",
                              l2cap_len, p_msg->len);

        GKI_freebuf (p_msg);
        return;
    }

    /* Send the data through the channel state machine */
    if (rcv_cid == L2CAP_SIGNALLING_CID)
    {
        process_l2cap_cmd (p_lcb, p, l2cap_len);
        GKI_freebuf (p_msg);
    }
    else if (rcv_cid == L2CAP_CONNECTIONLESS_CID)
    {
        /* process_connectionless_data (p_lcb); */
        STREAM_TO_UINT16 (psm, p);
        p_msg->offset += 2;
        p_msg->len    -= 2;
        L2CAP_TRACE_DEBUG1( "GOT CONNECTIONLESS DATA PSM:%d", psm ) ;
        GKI_freebuf (p_msg);
    }
    else
    {
        if (p_ccb == NULL)
            GKI_freebuf (p_msg);
        else
            l2c_csm_execute (p_ccb, L2CEVT_L2CAP_DATA, p_msg);
    }
}

/*******************************************************************************
**
** Function         process_l2cap_cmd
**
** Description      This function is called when a packet is received on the
**                  L2CAP signalling CID
**
** Returns          void
**
*******************************************************************************/
void process_l2cap_cmd (tL2C_LCB *p_lcb, UINT8 *p, UINT16 pkt_len)
{
    UINT8           *p_pkt_end, *p_next_cmd, *p_cfg_end, *p_cfg_start;
    UINT8           cmd_code, cfg_code, cfg_len, id;
    tL2C_CONN_INFO  con_info;
    tL2CAP_CFG_INFO cfg_info;
    UINT16          rej_reason, rej_mtu, lcid, rcid, info_type;
    tL2C_CCB        *p_ccb;
    tL2C_RCB        *p_rcb;
    BOOLEAN         cfg_rej;
    UINT16          cfg_rej_len, cmd_len;

    p_next_cmd = p;
    p_pkt_end  = p + pkt_len;

    /* An L2CAP packet may contain multiple commands */
    while (TRUE)
    {
        /* Smallest command is 4 bytes */
        if ((p = p_next_cmd) > (p_pkt_end - 4))
            break;

        STREAM_TO_UINT8  (cmd_code, p);
        STREAM_TO_UINT8  (id, p);
        STREAM_TO_UINT16 (cmd_len, p);

        /* Check command length does not exceed packet length */
        if ((p_next_cmd = p + cmd_len) > p_pkt_end)
        {
            L2CAP_TRACE_WARNING3 ("Command len bad  pkt_len: %d  cmd_len: %d  code: %d",
                                  pkt_len, cmd_len, cmd_code);
            break;
        }

        switch (cmd_code)
        {
        case L2CAP_CMD_REJECT:
            STREAM_TO_UINT16 (rej_reason, p);
            if (rej_reason == L2CAP_CMD_REJ_MTU_EXCEEDED)
            {
                STREAM_TO_UINT16 (rej_mtu, p);
                /* What to do with the MTU reject ? We have negotiated an MTU. For now */
                /* we will ignore it and let a higher protocol timeout take care of it */

                L2CAP_TRACE_WARNING2 ("L2CAP - MTU rej Handle: %d MTU: %d", p_lcb->handle, rej_mtu);
            }
            if (rej_reason == L2CAP_CMD_REJ_INVALID_CID)
            {
                STREAM_TO_UINT16 (rcid, p);
                STREAM_TO_UINT16 (lcid, p);

                L2CAP_TRACE_WARNING2 ("L2CAP - rej with CID invalid, LCID: %d RCID: %d", lcid, rcid);

                /* Remote CID invalid. Treat as a disconnect */
                if (((p_ccb = l2cu_find_ccb_by_cid (p_lcb, lcid)) != NULL)
                 && (p_ccb->remote_cid == rcid))
                {
                    /* Fake link disconnect - no reply is generated */
                    l2c_csm_execute (p_ccb, L2CEVT_LP_DISCONNECT_IND, NULL);
                }
            }
            break;

        case L2CAP_CMD_CONN_REQ:
            STREAM_TO_UINT16 (con_info.psm, p);
            STREAM_TO_UINT16 (rcid, p);
            if ((p_rcb = l2cu_find_rcb_by_psm (con_info.psm)) == NULL)
            {
                L2CAP_TRACE_WARNING1 ("L2CAP - rcvd conn req for unknown PSM: %d", con_info.psm);
                l2cu_reject_connection (p_lcb, rcid, id, L2CAP_CONN_NO_PSM);
                break;
            }
            if ((p_ccb = l2cu_allocate_ccb (p_lcb)) == NULL)
            {
                L2CAP_TRACE_ERROR0 ("L2CAP - unable to allocate CCB");
                l2cu_reject_connection (p_lcb, rcid, id, L2CAP_CONN_NO_RESOURCES);
                break;
            }
            p_ccb->remote_id = id;
            p_ccb->p_rcb = p_rcb;
            p_ccb->remote_cid = rcid;

            l2c_csm_execute(p_ccb, L2CEVT_L2CAP_CONNECT_REQ, &con_info);
            break;

        case L2CAP_CMD_CONN_RSP:
            STREAM_TO_UINT16 (con_info.remote_cid, p);
            STREAM_TO_UINT16 (lcid, p);
            STREAM_TO_UINT16 (con_info.l2cap_result, p);
            STREAM_TO_UINT16 (con_info.l2cap_status, p);

            if ((p_ccb = l2cu_find_ccb_by_cid (p_lcb, lcid)) == NULL)
            {
                L2CAP_TRACE_WARNING2 ("L2CAP - no CCB for conn rsp, LCID: %d RCID: %d",
                                      lcid, con_info.remote_cid);
                break;
            }
            if (p_ccb->local_id != id)
            {
                L2CAP_TRACE_WARNING2 ("L2CAP - con rsp - bad ID. Exp: %d Got: %d",
                                      p_ccb->local_id, id);
                break;
            }

            if (con_info.l2cap_result == L2CAP_CONN_OK)
                l2c_csm_execute(p_ccb, L2CEVT_L2CAP_CONNECT_RSP, &con_info);
            else if (con_info.l2cap_result == L2CAP_CONN_PENDING)
                l2c_csm_execute(p_ccb, L2CEVT_L2CAP_CONNECT_RSP_PND, &con_info);
            else
                l2c_csm_execute(p_ccb, L2CEVT_L2CAP_CONNECT_RSP_NEG, &con_info);

            break;

        case L2CAP_CMD_CONFIG_REQ:
            p_cfg_end = p + cmd_len;
            cfg_rej = FALSE;
            cfg_rej_len = 0;

            STREAM_TO_UINT16 (lcid, p);
            STREAM_TO_UINT16 (cfg_info.flags, p);

            p_cfg_start = p;

            cfg_info.flush_to_present = cfg_info.mtu_present = cfg_info.qos_present =
                cfg_info.fcr_present = FALSE;

            while (p < p_cfg_end)
            {
                STREAM_TO_UINT8 (cfg_code, p);
                STREAM_TO_UINT8 (cfg_len, p);

                switch (cfg_code & 0x7F)
                {
                case L2CAP_CFG_TYPE_MTU:
                    cfg_info.mtu_present = TRUE;
                    STREAM_TO_UINT16 (cfg_info.mtu, p);
                    break;

                case L2CAP_CFG_TYPE_FLUSH_TOUT:
                    cfg_info.flush_to_present = TRUE;
                    STREAM_TO_UINT16 (cfg_info.flush_to, p);
                    break;

                case L2CAP_CFG_TYPE_QOS:
                    cfg_info.qos_present = TRUE;
                    STREAM_TO_UINT8  (cfg_info.qos.qos_flags, p);
                    STREAM_TO_UINT8  (cfg_info.qos.service_type, p);
                    STREAM_TO_UINT32 (cfg_info.qos.token_rate, p);
                    STREAM_TO_UINT32 (cfg_info.qos.token_bucket_size, p);
                    STREAM_TO_UINT32 (cfg_info.qos.peak_bandwidth, p);
                    STREAM_TO_UINT32 (cfg_info.qos.latency, p);
                    STREAM_TO_UINT32 (cfg_info.qos.delay_variation, p);
                    break;

                case L2CAP_CFG_TYPE_FCR:
                    cfg_info.fcr_present = TRUE;
                    STREAM_TO_UINT8 (cfg_info.fcr.mode, p);
                    STREAM_TO_UINT8 (cfg_info.fcr.tx_win_sz, p);
                    STREAM_TO_UINT8 (cfg_info.fcr.max_transmit, p);
                    STREAM_TO_UINT16 (cfg_info.fcr.rtrans_tout, p);
                    STREAM_TO_UINT16 (cfg_info.fcr.mon_tout, p);
                    STREAM_TO_UINT16 (cfg_info.fcr.mps, p);
                    break;

                default:
                    /* sanity check option length */
                    if ((cfg_len + L2CAP_CFG_OPTION_OVERHEAD) <= cmd_len)
                    {
                        p += cfg_len;
                        if ((cfg_code & 0x80) == 0)
                        {
                            cfg_rej_len += cfg_len + L2CAP_CFG_OPTION_OVERHEAD;
                            cfg_rej = TRUE;
                        }
                    }
                    /* bad length; force loop exit */
                    else
                    {
                        p = p_cfg_end;
                    }
                    break;
                }
            }

            if ((p_ccb = l2cu_find_ccb_by_cid (p_lcb, lcid)) != NULL)
            {
                p_ccb->remote_id = id;
                if (cfg_rej)
                {
                    l2cu_send_peer_config_rej (p_ccb, p_cfg_start, (UINT16) (cmd_len - L2CAP_CONFIG_REQ_LEN), cfg_rej_len);
                }
                else
                {
                    l2c_csm_execute (p_ccb, L2CEVT_L2CAP_CONFIG_REQ, &cfg_info);
                }
            }
            else
            {
                /* updated spec says send command reject on invalid cid */
                l2cu_send_peer_cmd_reject (p_lcb, L2CAP_CMD_REJ_INVALID_CID, id, 0, 0);
            }
            break;

        case L2CAP_CMD_CONFIG_RSP:
            p_cfg_end = p + cmd_len;
            STREAM_TO_UINT16 (lcid, p);
            STREAM_TO_UINT16 (cfg_info.flags, p);
            STREAM_TO_UINT16 (cfg_info.result, p);

            cfg_info.fcr_present = cfg_info.flush_to_present = cfg_info.mtu_present =
                cfg_info.qos_present = FALSE;

            while (p < p_cfg_end)
            {
                STREAM_TO_UINT8 (cfg_code, p);
                STREAM_TO_UINT8 (cfg_len, p);

                switch (cfg_code & 0x7F)
                {
                case L2CAP_CFG_TYPE_MTU:
                    cfg_info.mtu_present = TRUE;
                    STREAM_TO_UINT16 (cfg_info.mtu, p);
                    break;

                case L2CAP_CFG_TYPE_FLUSH_TOUT:
                    cfg_info.flush_to_present = TRUE;
                    STREAM_TO_UINT16 (cfg_info.flush_to, p);
                    break;

                case L2CAP_CFG_TYPE_QOS:
                    cfg_info.qos_present = TRUE;
                    STREAM_TO_UINT8  (cfg_info.qos.qos_flags, p);
                    STREAM_TO_UINT8  (cfg_info.qos.service_type, p);
                    STREAM_TO_UINT32 (cfg_info.qos.token_rate, p);
                    STREAM_TO_UINT32 (cfg_info.qos.token_bucket_size, p);
                    STREAM_TO_UINT32 (cfg_info.qos.peak_bandwidth, p);
                    STREAM_TO_UINT32 (cfg_info.qos.latency, p);
                    STREAM_TO_UINT32 (cfg_info.qos.delay_variation, p);
                    break;

                case L2CAP_CFG_TYPE_FCR:
                    cfg_info.fcr_present = TRUE;
                    STREAM_TO_UINT8 (cfg_info.fcr.mode, p);
                    STREAM_TO_UINT8 (cfg_info.fcr.tx_win_sz, p);
                    STREAM_TO_UINT8 (cfg_info.fcr.max_transmit, p);
                    STREAM_TO_UINT16 (cfg_info.fcr.rtrans_tout, p);
                    STREAM_TO_UINT16 (cfg_info.fcr.mon_tout, p);
                    STREAM_TO_UINT16 (cfg_info.fcr.mps, p);
                    break;
                }
            }

            if ((p_ccb = l2cu_find_ccb_by_cid (p_lcb, lcid)) != NULL)
            {
                if (p_ccb->local_id != id)
                {
                    L2CAP_TRACE_WARNING2 ("L2CAP - cfg rsp - bad ID. Exp: %d Got: %d",
                                          p_ccb->local_id, id);
                    break;
                }
                if (cfg_info.result == L2CAP_CFG_OK)
                    l2c_csm_execute (p_ccb, L2CEVT_L2CAP_CONFIG_RSP, &cfg_info);
                else
                    l2c_csm_execute (p_ccb, L2CEVT_L2CAP_CONFIG_RSP_NEG, &cfg_info);
            }
            else
            {
                L2CAP_TRACE_WARNING1 ("L2CAP - rcvd cfg rsp for unknown CID: %d", lcid);
            }
            break;


        case L2CAP_CMD_DISC_REQ:
            STREAM_TO_UINT16 (lcid, p);
            STREAM_TO_UINT16 (rcid, p);

            if ((p_ccb = l2cu_find_ccb_by_cid (p_lcb, lcid)) != NULL)
            {
                if (p_ccb->remote_cid == rcid)
                {
                    p_ccb->remote_id = id;
                    l2c_csm_execute (p_ccb, L2CEVT_L2CAP_DISCONNECT_REQ, &con_info);
                }
            }
            else
                l2cu_send_peer_disc_rsp (p_lcb, id, lcid, rcid);

            break;

        case L2CAP_CMD_DISC_RSP:
            STREAM_TO_UINT16 (rcid, p);
            STREAM_TO_UINT16 (lcid, p);

            if ((p_ccb = l2cu_find_ccb_by_cid (p_lcb, lcid)) != NULL)
            {
                if ((p_ccb->remote_cid == rcid) && (p_ccb->local_id == id))
                {
                    l2c_csm_execute (p_ccb, L2CEVT_L2CAP_DISCONNECT_RSP, &con_info);
                }
            }
            break;

        case L2CAP_CMD_ECHO_REQ:
            if (cmd_len < (btu_cb.hcit_acl_pkt_size - L2CAP_PKT_OVERHEAD
                                                    - L2CAP_CMD_OVERHEAD
                                                    - L2CAP_ECHO_RSP_LEN
                                                    - HCI_DATA_PREAMBLE_SIZE))
            {
                l2cu_send_peer_echo_rsp (p_lcb, id, p, cmd_len);
            }
            else
            {
                l2cu_send_peer_echo_rsp (p_lcb, id, NULL, 0);
            }
            break;

        case L2CAP_CMD_ECHO_RSP:
            if (p_lcb->p_echo_rsp_cb)
            {
                tL2CA_ECHO_RSP_CB *p_cb = p_lcb->p_echo_rsp_cb;

                /* Zero out the callback in case app immediately calls us again */
                p_lcb->p_echo_rsp_cb = NULL;

                (*p_cb) (L2CAP_PING_RESULT_OK);
            }
            break;

        case L2CAP_CMD_INFO_REQ:
            STREAM_TO_UINT16 (info_type, p);
            l2cu_send_peer_info_rsp (p_lcb, id, info_type);
            break;

        case L2CAP_CMD_INFO_RSP:
            break;

        default:
            L2CAP_TRACE_WARNING1 ("L2CAP - bad cmd code: %d", cmd_code);
            l2cu_send_peer_cmd_reject (p_lcb, L2CAP_CMD_REJ_NOT_UNDERSTOOD, id, 0, 0);
            return;
        }
    }
}

/*******************************************************************************
**
** Function         l2c_process_timeout
**
** Description      This function is called when an L2CAP-related timeout occurs
**
** Returns          void
**
*******************************************************************************/
void l2c_process_timeout (TIMER_LIST_ENT *p_tle)
{
    /* What type of timeout ? */
    switch (p_tle->event)
    {
    case BTU_TTYPE_L2CAP_LINK:
        l2c_link_timeout ((tL2C_LCB *)p_tle->param);
        break;

    case BTU_TTYPE_L2CAP_CHNL:
        l2c_csm_execute (((tL2C_CCB *)p_tle->param), L2CEVT_TIMEOUT, NULL);
        break;

    case BTU_TTYPE_L2CAP_HOLD:
        /* Update the timeouts in the hold queue */
        l2c_process_held_packets(TRUE);
        break;

    case 73:
        break;
    }
}

/*******************************************************************************
**
** Function         l2c_process_held_packets
**
** Description      This function processes any L2CAP packets that arrived before
**                  the HCI connection complete arrived. It is a work around for
**                  badly behaved controllers.
**
** Returns          void
**
*******************************************************************************/
void l2c_process_held_packets (BOOLEAN timed_out)
{
    BT_HDR      *p_buf, *p_buf1;
    BUFFER_Q    *p_rcv_hold_q = &l2cb.rcv_hold_q;

    if (!p_rcv_hold_q->count)
        return;

    if (!timed_out)
    {
        btu_stop_timer(&l2cb.rcv_hold_tle);
        L2CAP_TRACE_WARNING0("L2CAP HOLD CONTINUE");
    }
    else
    {
        L2CAP_TRACE_WARNING0("L2CAP HOLD TIMEOUT");
    }

    /* Update the timeouts in the hold queue */
    for (p_buf = (BT_HDR *)GKI_getfirst (p_rcv_hold_q); p_buf; p_buf = p_buf1)
    {
        p_buf1 = (BT_HDR *)GKI_getnext (p_buf);
        if (!timed_out || (!p_buf->layer_specific) || (--p_buf->layer_specific == 0))
        {
            GKI_remove_from_queue (p_rcv_hold_q, p_buf);
            p_buf->layer_specific = 0xFFFF;
            l2c_rcv_acl_data (p_buf);
        }
    }

    /* If anyone still in the queue, restart the timeout */
    if (p_rcv_hold_q->count)
        btu_start_timer (&l2cb.rcv_hold_tle, BTU_TTYPE_L2CAP_HOLD, BT_1SEC_TIMEOUT);
}

#if 0
/*******************************************************************************
**
** Function         l2c_data_write
**
** Description      API functions call this function to write data.
**
** Returns          L2CAP_DW_SUCCESS, if data accepted, else FALSE
**                  L2CAP_DW_CONGESTED, if data accepted and the channel is congested
**                  L2CAP_DW_FAILED, if error
**
*******************************************************************************/
UINT8 l2c_data_write (UINT16 cid, BT_HDR *p_data, UINT16 flags)
{
    tL2C_CCB        *p_ccb;

    /* Find the channel control block. We don't know the link it is on. */
    if ((p_ccb = l2cu_find_ccb_by_cid (NULL, cid)) == NULL)
    {
        L2CAP_TRACE_WARNING1 ("L2CAP - no CCB for L2CA_DataWrite, CID: %d", cid);
        GKI_freebuf (p_data);
        return (L2CAP_DW_FAILED);
    }

#ifndef TESTER /* Tester may send any amount of data. otherwise sending message
                  bigger than mtu size of peer is a violation of protocol */
    if (p_data->len > p_ccb->peer_cfg.mtu)
    {
        L2CAP_TRACE_WARNING1 ("L2CAP - CID: 0x%04x  cannot send message bigger than peer's mtu size", cid);
        GKI_freebuf (p_data);
        return (L2CAP_DW_FAILED);
    }
#endif

    /* channel based, packet based flushable or non-flushable */
    p_data->layer_specific = flags;

    /* If already congested, do not accept any more packets */
    if (p_ccb->cong_sent)
    {
        L2CAP_TRACE_ERROR3 ("L2CAP - CID: 0x%04x cannot send, already congested  xmit_hold_q.count: %u  buff_quota: %u",
                            p_ccb->local_cid, p_ccb->xmit_hold_q.count, p_ccb->buff_quota);

        GKI_freebuf (p_data);
        return (L2CAP_DW_FAILED);
    }

    l2c_csm_execute (p_ccb, L2CEVT_L2CA_DATA_WRITE, p_data);

    if (p_ccb->cong_sent)
        return (L2CAP_DW_CONGESTED);

    return (L2CAP_DW_SUCCESS);
}
#endif
