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
 *  This file contains functions for the Bluetooth Security Manager
 *
 ******************************************************************************/

/* Wii (older BTE) structure layouts */
#define BTM_WII_LAYOUT
#define L2C_WII_LAYOUT
#define HCIC_WII_LAYOUT

/* Wii prototypes differ from the newer headers */
#define BTM_SecRegister             BTM_SecRegister_proto_unused
#define btm_sec_mx_access_request   btm_sec_mx_access_request_proto_unused
#define btm_sec_l2cap_access_req    btm_sec_l2cap_access_req_proto_unused
#define BTM_SetEncryption           BTM_SetEncryption_proto_unused
#include <string.h>
#include "bt_types.h"
#include "gki.h"
#include "hcimsgs.h"
#include "btu.h"
#include "btm_api.h"
#include "btm_int.h"
#include "l2c_int.h"
#undef BTM_SecRegister
#undef btm_sec_mx_access_request
#undef btm_sec_l2cap_access_req
#undef BTM_SetEncryption

/* Wii BTE (older build): bodies rewritten from the RSPE01_01 asm. Functions
** that were dead-stripped from the DOL are kept only for their trace strings,
** which remain in .data. */

#define BTM_WII_DEV_STATE_WAIT_AFTER_RESET  1
#define BTM_WII_SEC_MAX_SERVICES            46
#define BTM_WII_SEC_SERVICE_ARRAY_SIZE      2
#define BTM_WII_SEC_TIMEOUT_VALUE           30
#define BTM_WII_SEC_PIN_TIMEOUT             60

/* security_required flag used by the Wii stack for dedicated bonding (inferred) */
#define BTM_SEC_WII_BONDING                 0x40

#define BTM_SEC_STATE_IDLE              0
#define BTM_SEC_STATE_AUTHENTICATING    1
#define BTM_SEC_STATE_ENCRYPTING        2
#define BTM_SEC_STATE_GETTING_NAME      3
#define BTM_SEC_STATE_AUTHORIZING       4
#define BTM_SEC_STATE_DISCONNECTING     5

/* Wii hcic commands take a caller-allocated command buffer */
extern BOOLEAN btsnd_hcic_reject_conn (BT_HDR *p_buf, BD_ADDR bd_addr, UINT8 reason);

tBTM_STATUS btm_sec_execute_procedure (tBTM_SEC_DEV_REC *p_dev_rec);
UINT8       btm_sec_start_authorization (tBTM_SEC_DEV_REC *p_dev_rec);
void        btm_sec_collision_timeout (TIMER_LIST_ENT *p_tle);
void        btm_sec_pin_code_request_timeout (void);

/* Clear the RFCOMM channel of the current service of an originating device */
#define BTM_SEC_CLR_MX_CHAN(p_dev_rec) \
    if ((p_dev_rec)->is_originator && (p_dev_rec)->p_cur_service && \
        ((p_dev_rec)->p_cur_service->mx_proto_id == BTM_SEC_PROTO_RFCOMM)) \
        (p_dev_rec)->p_cur_service->orig_mx_chan_id = 0

/*******************************************************************************
** Inlined helpers
*******************************************************************************/
static tBTM_SEC_SERV_REC *btm_sec_find_first_serv (UINT16 psm)
{
    tBTM_SEC_SERV_REC *p_serv_rec = &btm_cb.sec_serv_rec[0];
    int i;

    for (i = 0; i < BTM_WII_SEC_MAX_SERVICE_RECORDS; i++, p_serv_rec++)
    {
        if ((p_serv_rec->security_flags & BTM_SEC_IN_USE) && (p_serv_rec->psm == psm))
            return(p_serv_rec);
    }
    return(NULL);
}

static tBTM_SEC_SERV_REC *btm_sec_find_next_serv (tBTM_SEC_SERV_REC *p_cur)
{
    tBTM_SEC_SERV_REC *p_serv_rec = &btm_cb.sec_serv_rec[0];
    BOOLEAN found = FALSE;
    int i;

    for (i = 0; i < BTM_WII_SEC_MAX_SERVICE_RECORDS; i++, p_serv_rec++)
    {
        if ((p_serv_rec->security_flags & BTM_SEC_IN_USE)
            && (p_serv_rec->psm == p_cur->psm) )
        {
            if (!found)
            {
                if (p_cur == p_serv_rec)
                    found = TRUE;
            }
            else
                return(p_serv_rec);
        }
    }
    return(NULL);
}

static tBTM_SEC_SERV_REC *btm_sec_find_mx_serv (UINT8 is_originator, UINT16 psm,
                                                UINT32 mx_proto_id, UINT32 mx_chan_id)
{
    tBTM_SEC_SERV_REC *p_serv_rec = &btm_cb.sec_serv_rec[0];
    int xx;

    for (xx = 0; xx < BTM_WII_SEC_MAX_SERVICE_RECORDS; xx++, p_serv_rec++)
    {
        if ((p_serv_rec->security_flags & BTM_SEC_IN_USE)
            && (p_serv_rec->psm == psm)
            && (p_serv_rec->mx_proto_id == mx_proto_id)
            && (( is_originator && (p_serv_rec->orig_mx_chan_id  == mx_chan_id))
                || (!is_originator && (p_serv_rec->term_mx_chan_id  == mx_chan_id))))
        {
            return(p_serv_rec);
        }
    }
    return(NULL);
}

static BOOLEAN btm_sec_are_all_trusted (UINT32 p_mask[])
{
    UINT32 trusted_inx;
    for (trusted_inx = 0; trusted_inx < BTM_WII_SEC_SERVICE_ARRAY_SIZE; trusted_inx++)
    {
        if (p_mask[trusted_inx] != BTM_SEC_TRUST_ALL)
            return(FALSE);
    }
    return(TRUE);
}

static BOOLEAN btm_sec_start_get_name (tBTM_SEC_DEV_REC *p_dev_rec)
{
    UINT8 tempstate = p_dev_rec->sec_state;

    p_dev_rec->sec_state = BTM_SEC_STATE_GETTING_NAME;

    if ((btm_initiate_rem_name (p_dev_rec->bd_addr, NULL, BTM_RMT_NAME_SEC,
                                BTM_WII_SEC_TIMEOUT_VALUE, NULL)) != BTM_CMD_STARTED)
    {
        p_dev_rec->sec_state = tempstate;
        return(FALSE);
    }

    return(TRUE);
}

static BOOLEAN btm_sec_start_authentication (tBTM_SEC_DEV_REC *p_dev_rec)
{
    p_dev_rec->sec_state = BTM_SEC_STATE_AUTHENTICATING;

    return(btsnd_hcic_auth_request (p_dev_rec->hci_handle));
}

static BOOLEAN btm_sec_start_encryption (tBTM_SEC_DEV_REC *p_dev_rec)
{
    if (!btsnd_hcic_set_conn_encrypt (p_dev_rec->hci_handle, TRUE))
        return(FALSE);

    p_dev_rec->sec_state = BTM_SEC_STATE_ENCRYPTING;
    return(TRUE);
}

static tBTM_STATUS btm_sec_dd_create_conn (tBTM_SEC_DEV_REC *p_dev_rec)
{
    tL2C_LCB *p_lcb;

    /* Make sure an L2cap link control block is available */
    if ((p_lcb = l2cu_allocate_lcb (p_dev_rec->bd_addr)) == NULL)
    {
        L2CAP_TRACE_WARNING0 ("L2CAP - no LCB for L2CA_conn_req");
        return(BTM_NO_RESOURCES);
    }

    if (l2cu_create_conn(p_lcb) == FALSE)
        return(BTM_NO_RESOURCES);

    p_dev_rec->is_originator = TRUE;
    return(BTM_CMD_STARTED);
}

static void btm_restore_mode (void)
{
    if (btm_cb.security_mode_changed)
    {
        btm_cb.security_mode_changed = FALSE;
        BTM_TRACE_DEBUG1 ("btm_restore_mode: Authen Enable -> %d", (btm_cb.security_mode == BTM_SEC_MODE_LINK));
        btsnd_hcic_write_auth_enable ((UINT8)(btm_cb.security_mode == BTM_SEC_MODE_LINK));
    }
    if (btm_cb.pin_type_changed)
    {
        btm_cb.pin_type_changed = FALSE;
        btsnd_hcic_write_pin_type (btm_cb.cfg.pin_type);
    }
}

/*******************************************************************************
**
** Function         BTM_SecRegister
**
*******************************************************************************/
BOOLEAN BTM_SecRegister (tBTM_APPL_INFO_WII *p_cb_info)
{
    btm_cb.api = *p_cb_info;

    BTM_TRACE_EVENT0 ("BTM_Sec: application registered");

    return(TRUE);
}

/*******************************************************************************
**
** Function         BTM_SecAddRmtNameNotifyCallback
**
*******************************************************************************/
BOOLEAN  BTM_SecAddRmtNameNotifyCallback (tBTM_RMT_NAME_CALLBACK *p_callback)
{
    int i;

    for (i = 0; i < 2; i++)
    {
        if (btm_cb.p_rmt_name_callback[i] == NULL)
        {
            btm_cb.p_rmt_name_callback[i] = p_callback;
            return(TRUE);
        }
    }

    return(FALSE);
}

/*******************************************************************************
**
** Function         BTM_SecDeleteRmtNameNotifyCallback
**
*******************************************************************************/
BOOLEAN  BTM_SecDeleteRmtNameNotifyCallback (tBTM_RMT_NAME_CALLBACK *p_callback)
{
    int i;

    for (i = 0; i < 2; i++)
    {
        if (btm_cb.p_rmt_name_callback[i] == p_callback)
        {
            btm_cb.p_rmt_name_callback[i] = NULL;
            return(TRUE);
        }
    }

    return(FALSE);
}

/*******************************************************************************
**
** Function         BTM_SetSecurityMode (dead-stripped; kept for its strings)
**
*******************************************************************************/
void BTM_SetSecurityMode (UINT8 security_mode)
{
    UINT8   old_mode = btm_cb.security_mode;

    BTM_TRACE_API1 ("BTM_SetSecurityMode: mode:%d", security_mode);

    btm_cb.security_mode = security_mode;

    /* If device is not up security mode will be set as a part of startup */
    if (btm_cb.devcb.state > BTM_WII_DEV_STATE_WAIT_AFTER_RESET)
    {
        if ((old_mode == BTM_SEC_MODE_LINK) && (security_mode != BTM_SEC_MODE_LINK))
        {
            BTM_TRACE_DEBUG0("BTM_SetSecurityMode: Authen Enable -> FALSE");
            btsnd_hcic_write_auth_enable (FALSE);
            btsnd_hcic_write_encr_mode (HCI_ENCRYPT_MODE_DISABLED);
        }
        else if ((old_mode != BTM_SEC_MODE_LINK) && (security_mode == BTM_SEC_MODE_LINK))
        {
            BTM_TRACE_DEBUG0("BTM_SetSecurityMode: Authen Enable -> TRUE");
            btsnd_hcic_write_auth_enable (TRUE);
            btsnd_hcic_write_encr_mode (HCI_ENCRYPT_MODE_POINT_TO_POINT);
        }
    }
}

/*******************************************************************************
**
** Function         BTM_SetPinType
**
*******************************************************************************/
void BTM_SetPinType (UINT8 pin_type, PIN_CODE pin_code, UINT8 pin_code_len)
{
    BTM_TRACE_API3 ("BTM_SetPinType: pin type %d [variable-0, fixed-1], code %s, length %d",
                    pin_type, (char *) pin_code, pin_code_len);

    /* If device is not up security mode will be set as a part of startup */
    if (btm_cb.devcb.state > BTM_WII_DEV_STATE_WAIT_AFTER_RESET)
        btsnd_hcic_write_pin_type (pin_type);

    btm_cb.cfg.pin_type     = pin_type;
    btm_cb.cfg.pin_code_len = pin_code_len;
    memcpy (btm_cb.cfg.pin_code, pin_code, pin_code_len);
}

/*******************************************************************************
**
** Function         BTM_SetSecurityLevel
**
*******************************************************************************/
BOOLEAN BTM_SetSecurityLevel (BOOLEAN is_originator, char *p_name, UINT8 service_id,
                              UINT16 sec_level, UINT16 psm, UINT32 mx_proto_id,
                              UINT32 mx_chan_id)
{
    tBTM_SEC_SERV_REC   *p_srec;
    UINT16               index;
    UINT16               first_unused_record = 0xFFFF;
    BOOLEAN              record_allocated = FALSE;

    /* See if the record can be reused (same service name, psm, mx_proto_id,
       service_id, and mx_chan_id), or obtain the next unused record */

    p_srec = &btm_cb.sec_serv_rec[0];

    for (index = 0; index < BTM_WII_SEC_MAX_SERVICE_RECORDS; index++, p_srec++)
    {
        /* Check if there is already a record for this service */
        if (p_srec->security_flags & BTM_SEC_IN_USE)
        {
            if (p_srec->psm == psm                  &&
                p_srec->mx_proto_id == mx_proto_id  &&
                service_id == p_srec->service_id    &&
                (!strncmp (p_name, (char *) p_srec->orig_service_name,
                           BTM_WII_SEC_SERVICE_NAME_LEN) ||
                 !strncmp (p_name, (char *) p_srec->term_service_name,
                           BTM_WII_SEC_SERVICE_NAME_LEN)))
            {
                record_allocated = TRUE;
                break;
            }
        }
        /* Mark the first available service record */
        else if (!record_allocated)
        {
            record_allocated = TRUE;
            first_unused_record = index;
        }
    }

    if (record_allocated)
    {
    /* Process the request if service record is valid */
    /* If a duplicate service wasn't found, use the first available */
    if (index >= BTM_WII_SEC_MAX_SERVICE_RECORDS)
    {
        index = first_unused_record;
        p_srec = &btm_cb.sec_serv_rec[index];
    }

    p_srec->psm         = psm;
    p_srec->service_id  = service_id;
    p_srec->mx_proto_id = mx_proto_id;

    if (is_originator)
    {
        p_srec->orig_mx_chan_id = mx_chan_id;
        /* clear out the old setting, just in case it exists */
        p_srec->security_flags &= ~(BTM_SEC_OUT_AUTHORIZE | BTM_SEC_OUT_ENCRYPT | BTM_SEC_OUT_AUTHENTICATE);
        strncpy ((char *)p_srec->orig_service_name, p_name, BTM_WII_SEC_SERVICE_NAME_LEN);
    }
    else
    {
        p_srec->term_mx_chan_id = mx_chan_id;
        /* clear out the old setting, just in case it exists */
        p_srec->security_flags &= ~(BTM_SEC_IN_AUTHORIZE | BTM_SEC_IN_ENCRYPT | BTM_SEC_IN_AUTHENTICATE);
        strncpy ((char *)p_srec->term_service_name, p_name, BTM_WII_SEC_SERVICE_NAME_LEN);
    }

    p_srec->security_flags |= sec_level | BTM_SEC_IN_USE;

    BTM_TRACE_API6("BTM_SEC_REG[%d]: id %d, is_orig %d, psm 0x%04x, proto_id %d, chan_id %d",
                   index, service_id, is_originator, psm, mx_proto_id, mx_chan_id);

    BTM_TRACE_API3("               : sec: 0x%x, service name [%s] (up to %d chars saved)",
                   p_srec->security_flags, p_name, BTM_WII_SEC_SERVICE_NAME_LEN);
    }
    else
    {
        BTM_TRACE_WARNING1("BTM_SEC_REG: Out of Service Records (%d)",  BTM_WII_SEC_MAX_SERVICE_RECORDS);
    }

    return(record_allocated);
}

/*******************************************************************************
**
** Function         BTM_PINCodeReply
**
*******************************************************************************/
void BTM_PINCodeReply (BD_ADDR bd_addr, UINT8 res, UINT8 pin_len, UINT8 *p_pin, UINT32 trusted_mask[])
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    if (btm_cb.pairing_tle.param)
    {
        btu_stop_timer (&btm_cb.pairing_tle);
        btm_cb.pairing_tle.param = 0;
        memset (btm_cb.pairing_bda, 0xff, BD_ADDR_LEN);

        if (res != BTM_SUCCESS)
        {
            btm_cb.acl_disc_reason = HCI_ERR_HOST_REJECT_SECURITY;
            btsnd_hcic_pin_code_neg_reply (bd_addr);
        }
        else
        {
            btm_cb.acl_disc_reason = HCI_SUCCESS;
            btsnd_hcic_pin_code_req_reply (bd_addr, pin_len, p_pin);

            if ((p_dev_rec = btm_find_dev (bd_addr)) != NULL)
            {
                p_dev_rec->trusted_mask[0] = trusted_mask[0];
                p_dev_rec->trusted_mask[1] = trusted_mask[1];
            }
        }
    }
}

/*******************************************************************************
**
** Function         BTM_DeviceAuthorized
**
*******************************************************************************/
void BTM_DeviceAuthorized (BD_ADDR bd_addr, UINT8 res, UINT32 trusted_mask[])
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    if ((p_dev_rec = btm_find_dev (bd_addr)) == NULL)
    {
        BTM_TRACE_WARNING6 ("Security Manager: Attempting Authorization of Unknown Device Address [%02x%02x%02x%02x%02x%02x]",
                            bd_addr[0], bd_addr[1], bd_addr[2], bd_addr[3], bd_addr[4], bd_addr[5]);
        return;
    }

    BTM_TRACE_EVENT2 ("Security Manager: authorized status:%d State:%d",
                      res, (p_dev_rec) ? p_dev_rec->sec_state : 0);

    if (res == BTM_SUCCESS)
    {
        p_dev_rec->sec_flags   |= BTM_SEC_AUTHORIZED;
        p_dev_rec->trusted_mask[0] = trusted_mask[0];
        p_dev_rec->trusted_mask[1] = trusted_mask[1];
    }

    if (p_dev_rec->sec_state != BTM_SEC_STATE_AUTHORIZING)
        return;

    p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;

    if (res != BTM_SUCCESS)
    {
        if (p_dev_rec->p_callback)
        {
            BTM_SEC_CLR_MX_CHAN(p_dev_rec);
            (*p_dev_rec->p_callback) (bd_addr, p_dev_rec->p_ref_data, res);
            p_dev_rec->p_callback = NULL;
        }
        return;
    }

    if ((res = btm_sec_execute_procedure (p_dev_rec)) != BTM_CMD_STARTED)
    {
        if (p_dev_rec->p_callback)
        {
            BTM_SEC_CLR_MX_CHAN(p_dev_rec);
            (*p_dev_rec->p_callback) (bd_addr, p_dev_rec->p_ref_data, res);
            p_dev_rec->p_callback = NULL;
        }
    }
}

/*******************************************************************************
**
** Function         BTM_SecBond
**
*******************************************************************************/
tBTM_STATUS BTM_SecBond (BD_ADDR bd_addr, UINT8 pin_len, UINT8 *p_pin, UINT32 trusted_mask[])
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    tBTM_INQ_INFO    *p_inq_info;
    BOOLEAN           allow_switch;
    BOOLEAN           status;

    BTM_TRACE_API6 ("BTM_SecBond BDA: %02x:%02x:%02x:%02x:%02x:%02x",
                    bd_addr[0], bd_addr[1], bd_addr[2], bd_addr[3], bd_addr[4], bd_addr[5]);

    if (pin_len > PIN_CODE_LEN)
    {
        BTM_TRACE_ERROR1 ("BTM_SecBond: Illegal Pin len:%d", pin_len);
        return(BTM_ILLEGAL_VALUE);
    }

    /* Find or get oldest record */
    if ((p_dev_rec = btm_find_dev (bd_addr)) == NULL)
    {
        if ((p_dev_rec = btm_sec_alloc_dev (bd_addr)) == NULL)
        {
            BTM_TRACE_ERROR0 ("BTM_SecBond: no device block");
            return(BTM_NO_RESOURCES);
        }
    }

    /* If connection already exists... */
    if ((p_dev_rec->hci_handle != BTM_SEC_INVALID_HANDLE)
        && (p_dev_rec->sec_flags & BTM_SEC_AUTHENTICATED))
    {
        BTM_TRACE_WARNING0("BTM_SecBond -> Already Paired");
        return(BTM_SUCCESS);
    }

    /* Tell controller to get rid of the link key if it has one stored */
    if ((BTM_DeleteStoredLinkKey (bd_addr, NULL)) != BTM_SUCCESS)
        return(BTM_NO_RESOURCES);

    p_dev_rec->security_required = BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_WII_BONDING;
    p_dev_rec->is_originator     = TRUE;
    p_dev_rec->trusted_mask[0]   = trusted_mask[0];
    p_dev_rec->trusted_mask[1]   = trusted_mask[1];

    btm_cb.pin_code_len = pin_len;

    if (pin_len)
        memcpy (btm_cb.pin_code, p_pin, pin_len);

    p_dev_rec->sec_flags &= ~(BTM_SEC_LINK_KEY_KNOWN | BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED);

    /* A keyboard needs a variable PIN */
    if (((p_dev_rec->dev_class[1] & BTM_COD_MAJOR_CLASS_MASK) == BTM_COD_MAJOR_PERIPHERAL)
        && (p_dev_rec->dev_class[2] & BTM_COD_MINOR_KEYBOARD)
        && (btm_cb.cfg.pin_type != HCI_PIN_TYPE_FIXED))
    {
        btm_cb.pin_type_changed = TRUE;
        btsnd_hcic_write_pin_type (HCI_PIN_TYPE_FIXED);
    }

    btm_cb.disc_reason = 0;

    /* If connection already exists... */
    if (p_dev_rec->hci_handle != BTM_SEC_INVALID_HANDLE)
    {
        p_dev_rec->sec_flags &= ~BTM_SEC_LINK_KEY_KNOWN;
        p_dev_rec->sec_state = BTM_SEC_STATE_AUTHENTICATING;

        if (!btsnd_hcic_auth_request (p_dev_rec->hci_handle))
            return(BTM_NO_RESOURCES);

        btm_cb.bond_created_conn = FALSE;
        return(BTM_CMD_STARTED);
    }

    if (btm_cb.security_mode != BTM_SEC_MODE_LINK)
    {
        BTM_TRACE_DEBUG0("BTM_SecBond: Authen Enable -> TRUE");
        if (!btsnd_hcic_write_auth_enable (TRUE))
        {
            BTM_TRACE_ERROR0 ("BTM_SecBond: no buffer");
            return(BTM_NO_RESOURCES);
        }
        btm_cb.security_mode_changed = TRUE;
    }

    btm_cb.bond_created_conn = TRUE;

    allow_switch = HCI_SWITCH_SUPPORTED(BTM_ReadLocalFeatures()) ? TRUE : FALSE;
    p_dev_rec->unk_85 = 0;

    if ((p_inq_info = BTM_InqDbRead(bd_addr)) != NULL)
    {
        status = btsnd_hcic_create_conn (bd_addr, HCI_PKT_TYPES_MASK_DM1 | HCI_PKT_TYPES_MASK_DH1,
                                         p_inq_info->results.page_scan_rep_mode,
                                         p_inq_info->results.page_scan_mode,
                                         (UINT16)(p_inq_info->results.clock_offset | BTM_CLOCK_OFFSET_VALID),
                                         allow_switch);
    }
    else
    {
        status = btsnd_hcic_create_conn (bd_addr, HCI_PKT_TYPES_MASK_DM1 | HCI_PKT_TYPES_MASK_DH1,
                                         HCI_PAGE_SCAN_REP_MODE_R1,
                                         HCI_MANDATARY_PAGE_SCAN_MODE,
                                         p_dev_rec->clock_offset, allow_switch);
    }

    if (status)
        return(BTM_CMD_STARTED);

    BTM_TRACE_ERROR0 ("BTM_SecBond: no buffer");

    if (btm_cb.security_mode_changed)
    {
        btm_cb.security_mode_changed = FALSE;
        BTM_TRACE_DEBUG1 ("btm_restore_mode: Authen Enable -> %d", (btm_cb.security_mode == BTM_SEC_MODE_LINK));
        btsnd_hcic_write_auth_enable ((UINT8)(btm_cb.security_mode == BTM_SEC_MODE_LINK));
    }

    return(BTM_NO_RESOURCES);
}

/*******************************************************************************
**
** Function         BTM_SetEncryption (dead-stripped; kept for its strings)
**
*******************************************************************************/
tBTM_STATUS BTM_SetEncryption (BD_ADDR bd_addr, tBTM_SEC_CALLBACK *p_callback,
                               void *p_ref_data)
{
    tBTM_SEC_DEV_REC  *p_dev_rec;
    tBTM_STATUS        rc;

    p_dev_rec = btm_find_dev (bd_addr);
    if (!p_dev_rec || (p_dev_rec->hci_handle == BTM_SEC_INVALID_HANDLE))
    {
        /* Connection should be up and runnning */
        BTM_TRACE_WARNING0 ("Security Manager: BTM_SetEncryption not connected");

        if (p_callback)
            (*p_callback) (bd_addr, p_ref_data, BTM_WRONG_MODE);

        return(BTM_WRONG_MODE);
    }

    if (p_dev_rec->sec_flags & BTM_SEC_ENCRYPTED)
    {
        BTM_TRACE_EVENT0 ("Security Manager: BTM_SetEncryption already encrypted");

        if (p_callback)
            (*p_callback) (bd_addr, p_ref_data, BTM_SUCCESS);

        return(BTM_SUCCESS);
    }

    if (p_dev_rec->p_callback)
    {
        /* Enqueue security request if security is active */
        BTM_TRACE_WARNING0 ("Security Manager: BTM_SetEncryption busy");

        if (p_callback)
            (*p_callback) (bd_addr, p_ref_data, BTM_BUSY);

        return(BTM_BUSY);
    }

    p_dev_rec->p_callback        = p_callback;
    p_dev_rec->p_ref_data        = p_ref_data;
    p_dev_rec->security_required |= (BTM_SEC_IN_AUTHENTICATE | BTM_SEC_IN_ENCRYPT);
    p_dev_rec->is_originator     = FALSE;

    BTM_TRACE_API4 ("Security Manager: BTM_SetEncryption Handle:%d State:%d Flags:0x%x Required:0x%x",
                    p_dev_rec->hci_handle, p_dev_rec->sec_state, p_dev_rec->sec_flags,
                    p_dev_rec->security_required);

    if ((rc = btm_sec_execute_procedure (p_dev_rec)) != BTM_CMD_STARTED)
    {
        if (p_callback)
        {
            (*p_callback) (bd_addr, p_dev_rec->p_ref_data, rc);
            p_dev_rec->p_callback = NULL;
        }
    }
    return(rc);
}

/*******************************************************************************
**
** Function         btm_sec_l2cap_access_req
**
*******************************************************************************/
tBTM_STATUS btm_sec_l2cap_access_req (BD_ADDR bd_addr, UINT16 psm, UINT16 handle,
                                      BOOLEAN is_originator, tBTM_SEC_CALLBACK *p_callback)
{
    tBTM_SEC_DEV_REC  *p_dev_rec;
    tBTM_SEC_SERV_REC *p_serv_rec;
    UINT8              security_required;
    tBTM_STATUS        rc;

    /* Find or get oldest record */
    if ((p_dev_rec = btm_find_dev (bd_addr)) == NULL)
    {
        if ((p_dev_rec = btm_sec_alloc_dev (bd_addr)) == NULL)
        {
            BTM_TRACE_WARNING1 ("Security Manager: l2cap_access_req PSM:%d no resources", psm);

            if (p_callback)
                (*p_callback) (bd_addr, NULL, BTM_NO_RESOURCES);

            return(BTM_NO_RESOURCES);
        }
    }

    p_dev_rec->hci_handle = handle;

    /* Find the service record for the PSM */
    p_serv_rec = btm_sec_find_first_serv (psm);

    /* If there is no application registered with this PSM do not allow connection */
    if (!p_serv_rec)
    {
        BTM_TRACE_WARNING1 ("Security Manager: l2cap_access_req PSM:%d no application registerd", psm);

        if (p_callback)
            (*p_callback) (bd_addr, NULL, BTM_MODE_UNSUPPORTED);

        return(BTM_MODE_UNSUPPORTED);
    }

    /* Save pointer to service record */
    if (!is_originator || (is_originator && !p_dev_rec->p_cur_service))
        p_dev_rec->p_cur_service = p_serv_rec;

    security_required = p_serv_rec->security_flags;

    /* If there are multiple service records for this PSM, the multiplexer will do the security */
    if (btm_sec_find_next_serv (p_serv_rec) != NULL)
    {
        BTM_TRACE_EVENT1 ("Security Manager: l2cap_access_req PSM:%d postponed for multiplexer", psm);

        if (p_callback)
            (*p_callback) (bd_addr, NULL, BTM_SUCCESS);

        return(BTM_SUCCESS);
    }

    p_dev_rec->p_callback        = p_callback;
    p_dev_rec->p_ref_data        = NULL;
    p_dev_rec->security_required = security_required;
    p_dev_rec->is_originator     = is_originator;

    BTM_TRACE_EVENT5 ("Security Manager: l2cap_access_req PSM:%d Handle:%d State:%d Flags:0x%x Required:0x%x",
                      psm, handle, p_dev_rec->sec_state, p_dev_rec->sec_flags, security_required);

    /* Although authentication and encryption are per connection */
    /* authorization is per access request. */
    if (!is_originator && (security_required & BTM_SEC_IN_AUTHORIZE))
    {
        p_dev_rec->sec_flags &= ~BTM_SEC_AUTHORIZED;
        BTM_TRACE_EVENT3 ("Security Manager: trusted:0x%04x%04x Flags:0x%x",
                          p_dev_rec->trusted_mask[1], p_dev_rec->trusted_mask[0], p_dev_rec->sec_flags);
    }

    if ((rc = btm_sec_execute_procedure (p_dev_rec)) != BTM_CMD_STARTED)
    {
        if (p_callback)
        {
            (*p_callback) (bd_addr, p_dev_rec->p_ref_data, (UINT8)rc);
            p_dev_rec->p_callback = NULL;
        }
    }

    return(rc);
}

/*******************************************************************************
**
** Function         btm_sec_mx_access_request
**
*******************************************************************************/
void btm_sec_mx_access_request (BD_ADDR bd_addr, UINT16 psm, BOOLEAN is_originator,
                                UINT32 mx_proto_id, UINT32 mx_chan_id,
                                tBTM_SEC_CALLBACK *p_callback, void *p_ref_data)
{
    tBTM_SEC_DEV_REC  *p_dev_rec;
    tBTM_SEC_SERV_REC *p_serv_rec;
    tBTM_STATUS        rc;

    /* Find or get oldest record */
    if ((p_dev_rec = btm_find_dev (bd_addr)) == NULL)
    {
        if ((p_dev_rec = btm_sec_alloc_dev (bd_addr)) == NULL)
        {
            if (p_callback)
                (*p_callback) (bd_addr, p_ref_data, BTM_NO_RESOURCES);
            return;
        }
    }

    /* Find the service record for the PSM */
    p_serv_rec = btm_sec_find_mx_serv (is_originator, psm, mx_proto_id, mx_chan_id);

    /* If there is no application registered with this PSM do not allow connection */
    if (!p_serv_rec)
    {
        if (p_callback)
            (*p_callback) (bd_addr, p_ref_data, BTM_MODE_UNSUPPORTED);

        BTM_TRACE_ERROR3 ("Security Manager: MX service not found PSM:%d Proto:%d SCN:%d",
                          psm, mx_proto_id, mx_chan_id);
        return;
    }

    /* Save pointer to service record */
    p_dev_rec->p_cur_service     = p_serv_rec;
    p_dev_rec->security_required = p_serv_rec->security_flags;
    p_dev_rec->is_originator     = is_originator;
    p_dev_rec->p_callback        = p_callback;
    p_dev_rec->p_ref_data        = p_ref_data;

    /* Although authentication and encryption are per connection */
    /* authorization is per access request. */
    p_dev_rec->sec_flags &= ~BTM_SEC_AUTHORIZED;

    if ((rc = btm_sec_execute_procedure (p_dev_rec)) != BTM_CMD_STARTED)
    {
        if (p_callback)
        {
            BTM_SEC_CLR_MX_CHAN(p_dev_rec);
            (*p_callback) (bd_addr, p_ref_data, (UINT8)rc);
            p_dev_rec->p_callback = NULL;
        }
    }
}

/*******************************************************************************
**
** Function         btm_sec_conn_req
**
*******************************************************************************/
void btm_sec_conn_req (UINT8 *bda, UINT8 *dc)
{
    tBTM_SEC_DEV_REC  *p_dev_rec;
    BT_HDR            *p_buf;

    /* Check if connection is allowed for only paired devices */
    if (btm_cb.connect_only_paired)
    {
        if (((p_dev_rec = btm_find_dev (bda)) == NULL) || !(p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_KNOWN))
        {
            BTM_TRACE_EVENT0 ("Security Manager: connect request from not paired device");

            /* Send HCI_Reject_Connection_Request */
            if ((p_buf = HCI_GET_CMD_BUF(0)) != NULL)
                btsnd_hcic_reject_conn (p_buf, bda, HCI_ERR_HOST_REJECT_DEVICE);
            return;
        }
    }

    /* If non-paired device is connecting, check if host wants to accept it */
    if (btm_cb.p_conn_filter_cb)
    {
        if (!(* btm_cb.p_conn_filter_cb) (bda, dc))
        {
            /* Send HCI_Reject_Connection_Request */
            if ((p_buf = HCI_GET_CMD_BUF(0)) != NULL)
                btsnd_hcic_reject_conn (p_buf, bda, HCI_ERR_HOST_REJECT_DEVICE);
            return;
        }
    }

    /* Host can be registered to verify comming BDA or DC */
    memcpy (btm_cb.connecting_bda, bda, BD_ADDR_LEN);
    memcpy (btm_cb.connecting_dc,  dc,  DEV_CLASS_LEN);

    l2c_link_hci_conn_req (bda);
}

/*******************************************************************************
**
** Function         btm_sec_init
**
*******************************************************************************/
void btm_sec_init (UINT8 sec_mode)
{
    btm_cb.security_mode = sec_mode;
    memset (btm_cb.pairing_bda, 0xff, BD_ADDR_LEN);
}

/*******************************************************************************
**
** Function         btm_sec_dev_reset
**
*******************************************************************************/
void btm_sec_dev_reset (void)
{
    if (btm_cb.security_mode == BTM_SEC_MODE_LINK)
    {
        btsnd_hcic_write_auth_enable (TRUE);
        btsnd_hcic_write_encr_mode (HCI_ENCRYPT_MODE_POINT_TO_POINT);
    }
}

/*******************************************************************************
**
** Function         btm_sec_abort_access_req
**
*******************************************************************************/
void btm_sec_abort_access_req (BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev (bd_addr);

    if (!p_dev_rec)
        return;

    if (btm_cb.api.p_abort_callback)
        (*btm_cb.api.p_abort_callback)(bd_addr, p_dev_rec->dev_class, p_dev_rec->sec_bd_name);

    if ((p_dev_rec->sec_state != BTM_SEC_STATE_AUTHORIZING)
        && (p_dev_rec->sec_state != BTM_SEC_STATE_AUTHENTICATING))
        return;

    p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;
    BTM_SEC_CLR_MX_CHAN(p_dev_rec);
    p_dev_rec->p_callback = NULL;
}

/*******************************************************************************
**
** Function         btm_sec_rmt_name_request_complete
**
*******************************************************************************/
void btm_sec_rmt_name_request_complete (UINT8 *p_bd_addr, UINT8 *p_bd_name, UINT8 status)
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    int               i;

    /* If remote name request failed, p_bd_addr is null and we need to search */
    /* based on state assuming that we are doing 1 at a time */
    if (p_bd_addr)
        p_dev_rec = btm_find_dev (p_bd_addr);
    else
    {
        p_dev_rec = &btm_cb.sec_dev_rec[0];

        for (i = 0; i < BTM_WII_SEC_MAX_DEVICE_RECORDS; i++, p_dev_rec++)
        {
            if ((p_dev_rec->sec_flags & BTM_SEC_IN_USE)
                && (p_dev_rec->sec_state == BTM_SEC_STATE_GETTING_NAME))
                break;
        }

        if (i == BTM_WII_SEC_MAX_DEVICE_RECORDS)
            p_dev_rec = NULL;
    }

    BTM_TRACE_EVENT2 ("Security Manager: rmt_name_complete status:%d State:%d",
                      status, (p_dev_rec) ? p_dev_rec->sec_state : 0);

    /* If unknown device we are done */
    if (!p_dev_rec)
        return;

    if (status == HCI_SUCCESS)
    {
        memcpy (p_dev_rec->sec_bd_name, p_bd_name, BTM_WII_MAX_REM_BD_NAME_LEN);
        p_dev_rec->sec_flags |= BTM_SEC_NAME_KNOWN;

        for (i = 0; i < 2; i++)
        {
            if (btm_cb.p_rmt_name_callback[i])
                (*btm_cb.p_rmt_name_callback[i])(p_bd_addr, p_dev_rec->dev_class,
                                                 p_dev_rec->sec_bd_name);
        }
    }

    /* If we were delaying asking UI for a PIN because name was not resolved, ask now */
    if (p_dev_rec->link_key_not_sent)
    {
        if ((p_dev_rec->security_required & BTM_SEC_WII_BONDING) && !p_dev_rec->unk_85)
            return;

        p_dev_rec->link_key_not_sent = FALSE;

        if (btm_cb.api.p_link_key_callback)
            (*btm_cb.api.p_link_key_callback) (p_dev_rec->bd_addr, p_dev_rec->dev_class,
                                               p_dev_rec->sec_bd_name, p_dev_rec->link_key,
                                               p_dev_rec->link_key_type);

        for (i = 0; i < 2; i++)
        {
            if (btm_cb.p_link_key_notif_cb[i])
                (*btm_cb.p_link_key_notif_cb[i]) (p_dev_rec->bd_addr, p_dev_rec->dev_class,
                                                  p_dev_rec->sec_bd_name, p_dev_rec->link_key,
                                                  p_dev_rec->link_key_type);
        }
    }

    /* If this is a bonding procedure can disconnect the link now */
    if ((p_dev_rec->security_required & BTM_SEC_WII_BONDING)
        && (p_dev_rec->sec_flags & BTM_SEC_AUTHENTICATED))
    {
        p_dev_rec->security_required &= ~(BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_WII_BONDING);
        btsnd_hcic_disconnect (p_dev_rec->hci_handle, HCI_ERR_PEER_USER);
        return;
    }

    /* If get name failed, notify the waiting layer */
    if (p_dev_rec->sec_state != BTM_SEC_STATE_GETTING_NAME)
        return;

    p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;

    if (status != HCI_SUCCESS)
    {
        if (p_dev_rec->p_callback)
        {
            (*p_dev_rec->p_callback) (p_dev_rec->bd_addr, p_dev_rec->p_ref_data, BTM_ERR_PROCESSING);
            p_dev_rec->p_callback = NULL;
        }
        return;
    }

    /* Security procedure was waiting for the name */
    if ((status = btm_sec_execute_procedure (p_dev_rec)) != BTM_CMD_STARTED)
    {
        if (p_dev_rec->p_callback)
        {
            (*p_dev_rec->p_callback) (p_dev_rec->bd_addr, p_dev_rec->p_ref_data, status);
            p_dev_rec->p_callback = NULL;
        }
    }
}

/*******************************************************************************
**
** Function         btm_sec_auth_complete
**
*******************************************************************************/
void btm_sec_auth_complete (UINT16 handle, UINT8 status)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev_by_handle (handle);
    UINT8             res;

    BTM_TRACE_EVENT2 ("Security Manager: auth_complete status:%d State:%d",
                      status, (p_dev_rec) ? p_dev_rec->sec_state : 0);

    /* We do not know which device is bonding, restore pin type/security mode */
    btm_restore_mode();

    /* If this is a bonding procedure over an existing link, disconnect if asked to */
    if (p_dev_rec && (p_dev_rec->security_required & BTM_SEC_WII_BONDING)
        && !btm_cb.bond_created_conn)
    {
        p_dev_rec->security_required &= ~(BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_WII_BONDING);

        if (btm_cb.disc_reason)
            btm_sec_disconnect (handle, btm_cb.disc_reason);
    }

    if (!p_dev_rec)
        return;

    /* If authentication failed and we are not in the authenticating state, notify */
    if (p_dev_rec->sec_state != BTM_SEC_STATE_AUTHENTICATING)
    {
        if ((btm_cb.api.p_auth_complete_callback) && (status != HCI_SUCCESS))
            (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr, p_dev_rec->dev_class,
                                                    p_dev_rec->sec_bd_name, status);
        return;
    }

    /* There can be a race condition, when we are starting authentication and */
    /* the peer device is doing encryption. */
    if ((status == HCI_ERR_COMMAND_DISALLOWED)
        && ((p_dev_rec->sec_flags & (BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED)) ==
            (BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED)))
    {
        status = HCI_SUCCESS;
    }

    if (btm_cb.api.p_auth_complete_callback)
        (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr, p_dev_rec->dev_class,
                                                p_dev_rec->sec_bd_name, status);

    p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;

    /* If this is a bonding procedure can disconnect the link now */
    if (p_dev_rec->security_required & BTM_SEC_WII_BONDING)
    {
        p_dev_rec->security_required &= ~(BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_WII_BONDING);
        btsnd_hcic_disconnect (p_dev_rec->hci_handle, HCI_ERR_PEER_USER);
        return;
    }

    if (status != HCI_SUCCESS)
    {
        if (p_dev_rec->p_callback)
        {
            BTM_SEC_CLR_MX_CHAN(p_dev_rec);
            (*p_dev_rec->p_callback) (p_dev_rec->bd_addr, p_dev_rec->p_ref_data, BTM_ERR_PROCESSING);
            p_dev_rec->p_callback = NULL;
        }

        btsnd_hcic_disconnect (p_dev_rec->hci_handle, HCI_ERR_AUTH_FAILURE);
        return;
    }

    p_dev_rec->sec_flags |= BTM_SEC_AUTHENTICATED;

    /* Authentication succeeded, execute the next security procedure, if any */
    /* If there is no next procedure, or procedure failed to start, notify the caller */
    if ((res = btm_sec_execute_procedure (p_dev_rec)) != BTM_CMD_STARTED)
    {
        if (p_dev_rec->p_callback)
        {
            BTM_SEC_CLR_MX_CHAN(p_dev_rec);
            (*p_dev_rec->p_callback) (p_dev_rec->bd_addr, p_dev_rec->p_ref_data, res);
            p_dev_rec->p_callback = NULL;
        }
    }
}

/*******************************************************************************
**
** Function         btm_sec_mkey_comp_event
**
*******************************************************************************/
void btm_sec_mkey_comp_event (UINT16 handle, UINT8 status, UINT8 key_flg)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev_by_handle (handle);
    UINT8             bd_addr[BD_ADDR_LEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    BTM_TRACE_EVENT2 ("Security Manager: mkey comp status:%d State:%d",
                      status, (p_dev_rec) ? p_dev_rec->sec_state : 0);

    /* If link is being disconnected or not, notify upper layer */
    if (btm_cb.mkey_cback)
    {
        if (!p_dev_rec)
            (btm_cb.mkey_cback)(bd_addr, status, key_flg );
        else
            (btm_cb.mkey_cback)(p_dev_rec->bd_addr, status, key_flg );
    }
}

/*******************************************************************************
**
** Function         btm_sec_encrypt_change
**
*******************************************************************************/
void btm_sec_encrypt_change (UINT16 handle, UINT8 status, UINT8 encr_enable)
{
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev_by_handle (handle);

    BTM_TRACE_EVENT2 ("Security Manager: encrypt_change status:%d State:%d",
                      status, (p_dev_rec) ? p_dev_rec->sec_state : 0);

    /* For transaction collision we need to wait and repeat.  There is no need */
    /* for random timeout because only slave should receive the result */
    if (!p_dev_rec)
        return;

    if (status == HCI_ERR_LMP_ERR_TRANS_COLLISION)
    {
        btm_cb.p_collided_dev_rec = p_dev_rec;
        btm_cb.sec_collision_tle.param = (TIMER_PARAM_TYPE) btm_sec_collision_timeout;
        btu_start_timer (&btm_cb.sec_collision_tle, BTU_TTYPE_USER_FUNC, 1);
        return;
    }

    /* If encryption setup failed, notify the waiting layer */
    if (status != HCI_SUCCESS)
    {
        if (p_dev_rec->p_callback)
        {
            (*p_dev_rec->p_callback) (p_dev_rec->bd_addr, p_dev_rec->p_ref_data, BTM_ERR_PROCESSING);
            p_dev_rec->p_callback = NULL;
        }
        return;
    }

    p_dev_rec->sec_flags |= (BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED);

    if (p_dev_rec->sec_state != BTM_SEC_STATE_ENCRYPTING)
        return;

    p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;

    /* Encryption setup succeeded, execute the next security procedure, if any */
    if ((status = btm_sec_execute_procedure (p_dev_rec)) != BTM_CMD_STARTED)
    {
        if (p_dev_rec->p_callback)
        {
            (*p_dev_rec->p_callback) (p_dev_rec->bd_addr, p_dev_rec->p_ref_data, status);
            p_dev_rec->p_callback = NULL;
        }
    }
}

/*******************************************************************************
**
** Function         btm_sec_is_bonding
**
*******************************************************************************/
BOOLEAN btm_sec_is_bonding (UINT16 handle)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev_by_handle (handle);

    if (p_dev_rec && (p_dev_rec->security_required & BTM_SEC_WII_BONDING))
        return(TRUE);

    return(FALSE);
}

/*******************************************************************************
**
** Function         btm_sec_connected
**
*******************************************************************************/
void btm_sec_connected (UINT8 *bda, UINT16 handle, UINT8 status, UINT8 enc_mode)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev (bda);
    UINT8             res;
    int               i;

    BTM_TRACE_EVENT3 ("Security Manager: btm_sec_connected handle:%d status:%d enc_mode:%d",
                      handle, status, enc_mode);

    if (!p_dev_rec)
    {
        /* There is no device record for new connection.  Allocate one */
        if (status == HCI_SUCCESS)
        {
            if ((p_dev_rec = btm_sec_alloc_dev (bda)) == NULL)
                return;
        }
        else
        {
            /* can not find the device record and this is not a successful connection */
            return;
        }
    }
    else    /* Update the timestamp for this device */
    {
        p_dev_rec->timestamp = btm_cb.dev_rec_count++;
        p_dev_rec->unk_85 = TRUE;
    }

    /* If this is a bonding procedure, restore the security mode and pin type */
    if (p_dev_rec->security_required & BTM_SEC_WII_BONDING)
        btm_restore_mode();

    if (status != HCI_SUCCESS)
    {
        if ((status == HCI_ERR_AUTH_FAILURE)                  ||
            (status == HCI_ERR_KEY_MISSING)                   ||
            (status == HCI_ERR_HOST_REJECT_SECURITY)          ||
            (status == HCI_ERR_PAIRING_NOT_ALLOWED)           ||
            (status == HCI_ERR_UNIT_KEY_USED)                 ||
            (status == HCI_ERR_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED) ||
            (status == HCI_ERR_ENCRY_MODE_NOT_ACCEPTABLE)     ||
            (status == HCI_ERR_REPEATED_ATTEMPTS)             ||
            (status == HCI_ERR_LMP_RESPONSE_TIMEOUT)          ||
            (p_dev_rec->security_required & BTM_SEC_WII_BONDING))
        {
            p_dev_rec->security_required &= ~(BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_WII_BONDING);
            p_dev_rec->sec_flags &= ~BTM_SEC_LINK_KEY_KNOWN;

            /* Stop the PIN timer if the user did not answer */
            if (btm_cb.pairing_tle.param)
            {
                btu_stop_timer (&btm_cb.pairing_tle);
                btm_cb.pairing_tle.param = 0;
                status = HCI_ERR_HOST_REJECT_SECURITY;
            }

            if (btm_cb.acl_disc_reason == HCI_ERR_HOST_REJECT_SECURITY)
                status = HCI_ERR_HOST_REJECT_SECURITY;

            if (btm_cb.api.p_auth_complete_callback)
                (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr, p_dev_rec->dev_class,
                                                        p_dev_rec->sec_bd_name, status);
            return;
        }

        if (p_dev_rec->p_callback)
        {
            BTM_SEC_CLR_MX_CHAN(p_dev_rec);

            /* Report the error */
            if ((status == HCI_ERR_CONNECTION_TOUT) || (status == HCI_ERR_UNSPECIFIED)
                || (status == HCI_ERR_PAGE_TIMEOUT))
                (*p_dev_rec->p_callback) (p_dev_rec->bd_addr, p_dev_rec->p_ref_data, BTM_DEVICE_TIMEOUT);
            else
                (*p_dev_rec->p_callback) (p_dev_rec->bd_addr, p_dev_rec->p_ref_data, BTM_ERR_PROCESSING);
        }
        return;
    }

    /* If initiated dedicated bonding, return the link key now, and initiate disconnect */
    if ((p_dev_rec->security_required & BTM_SEC_WII_BONDING) && p_dev_rec->link_key_not_sent)
    {
        p_dev_rec->link_key_not_sent = FALSE;

        if (btm_cb.api.p_link_key_callback)
            (*btm_cb.api.p_link_key_callback) (p_dev_rec->bd_addr, p_dev_rec->dev_class,
                                               p_dev_rec->sec_bd_name, p_dev_rec->link_key,
                                               p_dev_rec->link_key_type);

        for (i = 0; i < 2; i++)
        {
            if (btm_cb.p_link_key_notif_cb[i])
                (*btm_cb.p_link_key_notif_cb[i]) (p_dev_rec->bd_addr, p_dev_rec->dev_class,
                                                  p_dev_rec->sec_bd_name, p_dev_rec->link_key,
                                                  p_dev_rec->link_key_type);
        }

        if (btm_cb.api.p_auth_complete_callback)
            (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr, p_dev_rec->dev_class,
                                                    p_dev_rec->sec_bd_name, HCI_SUCCESS);

        p_dev_rec->security_required &= ~(BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_WII_BONDING);
        btsnd_hcic_disconnect (handle, HCI_ERR_PEER_USER);
        return;
    }

    p_dev_rec->hci_handle = handle;

    /* After connection is established the link is not authenticated/encrypted yet */
    p_dev_rec->sec_flags &= ~(BTM_SEC_AUTHORIZED | BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED);

    if (enc_mode != HCI_ENCRYPT_MODE_DISABLED)
        p_dev_rec->sec_flags |= (BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED);

    if (btm_cb.security_mode == BTM_SEC_MODE_LINK)
        p_dev_rec->sec_flags |= BTM_SEC_AUTHENTICATED;

    p_dev_rec->unk_84 = 0;

    /* After connection is established we perform security if we do not know */
    /* the name, or if we are originator because some procedure can have */
    /* been scheduled while connection was down */
    if (!(p_dev_rec->sec_flags & BTM_SEC_NAME_KNOWN) || p_dev_rec->is_originator)
    {
        if ((res = btm_sec_execute_procedure (p_dev_rec)) != BTM_CMD_STARTED)
        {
            if (p_dev_rec->p_callback)
            {
                BTM_SEC_CLR_MX_CHAN(p_dev_rec);
                (*p_dev_rec->p_callback) (p_dev_rec->bd_addr, p_dev_rec->p_ref_data, res);
                p_dev_rec->p_callback = NULL;
            }
        }
    }
}

/*******************************************************************************
**
** Function         btm_sec_disconnect
**
*******************************************************************************/
tBTM_STATUS btm_sec_disconnect (UINT16 handle, UINT8 reason)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev_by_handle (handle);
    UINT8             old_state;

    /* In some weird race condition we may not have a record */
    if (!p_dev_rec)
        return(BTM_ILLEGAL_VALUE);

    /* If we are in the process of bonding we need to tell client that auth failed */
    if (p_dev_rec->security_required & BTM_SEC_WII_BONDING)
    {
        /* we are currently doing bonding.  Disconnection should happen when bond is done */
        btm_cb.disc_reason = reason;
        return(BTM_SUCCESS);
    }

    old_state = p_dev_rec->sec_state;

    if (old_state == BTM_SEC_STATE_DISCONNECTING)
        return(BTM_CMD_STARTED);

    p_dev_rec->sec_state = BTM_SEC_STATE_DISCONNECTING;

    if (btsnd_hcic_disconnect (handle, reason))
        return(BTM_CMD_STARTED);

    p_dev_rec->sec_state = old_state;
    return(BTM_NO_RESOURCES);
}

/*******************************************************************************
**
** Function         btm_sec_disconnected
**
*******************************************************************************/
void btm_sec_disconnected (UINT16 handle, UINT8 reason)
{
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_dev_by_handle (handle);

    if (!p_dev_rec)
        return;

    /* If we are in the process of bonding we need to tell client that auth failed */
    if ((p_dev_rec->security_required & BTM_SEC_WII_BONDING)
        && (btm_cb.api.p_auth_complete_callback))
    {
        if (reason == HCI_ERR_REPEATED_ATTEMPTS)
            (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr, p_dev_rec->dev_class,
                                                    p_dev_rec->sec_bd_name, HCI_ERR_REPEATED_ATTEMPTS);
        else
            (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr, p_dev_rec->dev_class,
                                                    p_dev_rec->sec_bd_name, HCI_ERR_AUTH_FAILURE);
    }

    /* If the link went down while the user was asked for a PIN, cancel it */
    if (btm_cb.pairing_tle.param
        && !memcmp (btm_cb.pairing_bda, p_dev_rec->bd_addr, BD_ADDR_LEN))
    {
        btu_stop_timer (&btm_cb.pairing_tle);
        btm_cb.pairing_tle.param = 0;
        memset (btm_cb.pairing_bda, 0xff, BD_ADDR_LEN);

        if (btm_cb.api.p_auth_complete_callback)
            (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr, p_dev_rec->dev_class,
                                                    p_dev_rec->sec_bd_name, HCI_ERR_HOST_REJECT_SECURITY);
    }

    p_dev_rec->hci_handle = BTM_SEC_INVALID_HANDLE;
    p_dev_rec->sec_state  = BTM_SEC_STATE_IDLE;
    p_dev_rec->sec_flags &= ~(BTM_SEC_AUTHORIZED | BTM_SEC_AUTHENTICATED | BTM_SEC_ENCRYPTED);
    p_dev_rec->security_required &= BTM_SEC_IN_USE;
    p_dev_rec->p_callback = NULL;
}

/*******************************************************************************
**
** Function         btm_sec_link_key_notification
**
*******************************************************************************/
void btm_sec_link_key_notification (UINT8 *p_bda, UINT8 *p_link_key, UINT8 key_type)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev (p_bda);
    int               i;

    /* Find or get oldest record */
    if (!p_dev_rec)
    {
        if ((p_dev_rec = btm_sec_alloc_dev (p_bda)) == NULL)
            return;
    }

    BTM_TRACE_EVENT6 ("btm_sec_link_key_notification()  BDA: %02x:%02x:%02x:%02x:%02x:%02x",
                      p_bda[0], p_bda[1], p_bda[2], p_bda[3], p_bda[4], p_bda[5]);
    BTM_TRACE_EVENT1 ("                                TYPE: %d", key_type);

    /* Before 1.1 controllers did not report the key type */
    if (btm_cb.devcb.local_version.hci_version < 1 /* HCI 1.1 */)
        p_dev_rec->link_key_type = 0xFF;
    else
        p_dev_rec->link_key_type = key_type;

    p_dev_rec->sec_flags |= BTM_SEC_LINK_KEY_KNOWN;
    memcpy (p_dev_rec->link_key, p_link_key, LINK_KEY_LEN);

    /* If name is not known at this point delay calling callback until the name is   */
    /* resolved. */
    if (!(p_dev_rec->sec_flags & BTM_SEC_NAME_KNOWN)
        || ((p_dev_rec->security_required & BTM_SEC_WII_BONDING) && !p_dev_rec->unk_85))
    {
        p_dev_rec->link_key_not_sent = TRUE;
        return;
    }

    /* We will save link key only if the user authorized it - BTE report link key in all cases */
    if (btm_cb.api.p_link_key_callback)
        (*btm_cb.api.p_link_key_callback) (p_bda, p_dev_rec->dev_class, p_dev_rec->sec_bd_name,
                                           p_link_key, p_dev_rec->link_key_type);

    for (i = 0; i < 2; i++)
    {
        if (btm_cb.p_link_key_notif_cb[i])
            (*btm_cb.p_link_key_notif_cb[i]) (p_bda, p_dev_rec->dev_class, p_dev_rec->sec_bd_name,
                                              p_link_key, p_dev_rec->link_key_type);
    }
}

/*******************************************************************************
**
** Function         btm_sec_link_key_request
**
*******************************************************************************/
void btm_sec_link_key_request (UINT8 *p_bda)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev (p_bda);
    LINK_KEY          link_key;

    BTM_TRACE_EVENT6 ("btm_sec_link_key_request()  BDA: %02x:%02x:%02x:%02x:%02x:%02x",
                      p_bda[0], p_bda[1], p_bda[2], p_bda[3], p_bda[4], p_bda[5]);

    if (p_dev_rec && (p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_KNOWN))
    {
        btsnd_hcic_link_key_req_reply (p_bda, p_dev_rec->link_key);
        return;
    }

    if (!p_dev_rec)
        p_dev_rec = btm_sec_alloc_dev (p_bda);

    /* Ask the application for the link key, unless this is dedicated bonding */
    if (!(p_dev_rec->security_required & BTM_SEC_WII_BONDING) && btm_cb.api.p_link_key_req_callback)
    {
        if (p_dev_rec)
        {
            if ((*btm_cb.api.p_link_key_req_callback)(p_bda, p_dev_rec->link_key) == BTM_SUCCESS)
            {
                btsnd_hcic_link_key_req_reply (p_bda, p_dev_rec->link_key);
                return;
            }
        }
        else
        {
            if ((*btm_cb.api.p_link_key_req_callback)(p_bda, link_key) == BTM_SUCCESS)
            {
                btsnd_hcic_link_key_req_reply (p_bda, link_key);
                return;
            }
        }
    }

    /* The link key is not in the database and it is not known to the manager */
    btsnd_hcic_link_key_neg_reply (p_bda);
}

/*******************************************************************************
**
** Function         btm_sec_pin_code_request_timeout
**
*******************************************************************************/
void btm_sec_pin_code_request_timeout (void)
{
    tBTM_CB *p_cb = &btm_cb;

    BTM_TRACE_EVENT0 ("btm_sec_pin_code_request_timeout()");

    p_cb->pairing_tle.param = 0;
    memset (btm_cb.pairing_bda, 0xff, BD_ADDR_LEN);
    btsnd_hcic_pin_code_neg_reply (p_cb->connecting_bda);
}

/*******************************************************************************
**
** Function         btm_sec_pin_code_request
**
*******************************************************************************/
void btm_sec_pin_code_request (UINT8 *p_bda)
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    tBTM_CB          *p_cb = &btm_cb;
    BOOLEAN           reject = FALSE;
    int               i = 0;

    BTM_TRACE_EVENT6 ("btm_sec_pin_code_request()  BDA: %02x:%02x:%02x:%02x:%02x:%02x",
                      p_bda[0], p_bda[1], p_bda[2], p_bda[3], p_bda[4], p_bda[5]);

    /* Fixed PIN: answer right away if there is room for the device */
    if (!p_cb->pairing_disabled && (p_cb->cfg.pin_type == HCI_PIN_TYPE_FIXED))
    {
        if (btm_find_dev (p_bda) == NULL)
        {
            p_dev_rec = &btm_cb.sec_dev_rec[0];
            for (; i < BTM_WII_SEC_MAX_DEVICE_RECORDS; i++, p_dev_rec++)
            {
                if (!(p_dev_rec->sec_flags & BTM_SEC_IN_USE))
                    break;
            }
        }

        if (i >= BTM_WII_SEC_MAX_DEVICE_RECORDS)
            btsnd_hcic_pin_code_neg_reply (p_bda);
        else
            btsnd_hcic_pin_code_req_reply (p_bda, p_cb->cfg.pin_code_len, p_cb->cfg.pin_code);
        return;
    }

    /* Use the connecting device's BDA if we don't have a record */
    if ((p_dev_rec = btm_find_dev (p_bda)) == NULL)
        p_dev_rec = btm_sec_alloc_dev (p_bda);

    memcpy (btm_cb.pairing_bda, p_bda, BD_ADDR_LEN);

    if (p_dev_rec)
    {
        if (!memcmp (p_bda, p_cb->connecting_bda, BD_ADDR_LEN))
            memcpy (p_dev_rec->dev_class, p_cb->connecting_dc, DEV_CLASS_LEN);

        /* We have the PIN code for dedicated bonding */
        if (p_dev_rec->security_required & BTM_SEC_WII_BONDING)
        {
            BTM_TRACE_EVENT0 ("btm_sec_pin_code_request bonding sending reply");
            btsnd_hcic_pin_code_req_reply (p_bda, p_cb->pin_code_len, p_cb->pin_code);

            if (btm_cb.security_mode_changed)
            {
                btm_cb.security_mode_changed = FALSE;
                BTM_TRACE_DEBUG1 ("btm_sec_pin_code_request: Authen Enable -> %d",
                                  (btm_cb.security_mode == BTM_SEC_MODE_LINK));
                btsnd_hcic_write_auth_enable ((UINT8)(btm_cb.security_mode == BTM_SEC_MODE_LINK));
            }
        }
        else if (p_cb->pairing_disabled || !p_cb->api.p_pin_callback
                 || (!p_dev_rec->is_originator
                     && ((p_dev_rec->dev_class[1] & BTM_COD_MAJOR_CLASS_MASK) == BTM_COD_MAJOR_PERIPHERAL)
                     && (p_dev_rec->dev_class[2] & BTM_COD_MINOR_KEYBOARD)))
        {
            reject = TRUE;
        }
        else
        {
            memcpy (p_cb->connecting_bda, p_bda, BD_ADDR_LEN);
            memcpy (p_cb->connecting_dc, p_dev_rec->dev_class, DEV_CLASS_LEN);

            p_cb->pairing_tle.param = (TIMER_PARAM_TYPE) btm_sec_pin_code_request_timeout;
            btu_start_timer (&p_cb->pairing_tle, BTU_TTYPE_USER_FUNC, BTM_WII_SEC_PIN_TIMEOUT);

            (*p_cb->api.p_pin_callback) (p_bda, p_dev_rec->dev_class, p_dev_rec->sec_bd_name);
        }
    }
    else
        reject = TRUE;

    if (reject)
    {
        BTM_TRACE_WARNING3 ("btm_sec_pin_code_request(): Pairing disabled:%d; PIN callback:%x, Dev Rec:%x!",
                            p_cb->pairing_disabled, p_cb->api.p_pin_callback, p_dev_rec);

        btsnd_hcic_pin_code_neg_reply (p_bda);
    }
}

/*******************************************************************************
**
** Function         btm_sec_update_clock_offset
**
*******************************************************************************/
void btm_sec_update_clock_offset (UINT16 handle, UINT16 clock_offset)
{
    tBTM_SEC_DEV_REC  *p_dev_rec;
    tBTM_INQ_INFO     *p_inq_info;

    if ((p_dev_rec = btm_find_dev_by_handle (handle)) == NULL)
        return;

    clock_offset |= BTM_CLOCK_OFFSET_VALID;
    p_dev_rec->clock_offset = clock_offset;

    if ((p_inq_info = BTM_InqDbRead(p_dev_rec->bd_addr)) == NULL)
        return;

    p_inq_info->results.clock_offset = clock_offset;
}

/*******************************************************************************
**
** Function         btm_sec_execute_procedure
**
*******************************************************************************/
tBTM_STATUS btm_sec_execute_procedure (tBTM_SEC_DEV_REC *p_dev_rec)
{
    BTM_TRACE_EVENT3 ("btm_sec_execute_procedure: Required:0x%x Flags:0x%x State:%d",
                      p_dev_rec->security_required, p_dev_rec->sec_flags, p_dev_rec->sec_state);

    /* There is a chance that we are getting name.  Wait until done. */
    if (p_dev_rec->sec_state != BTM_SEC_STATE_IDLE)
        return(BTM_CMD_STARTED);

    /* If there is no connection, create one first */
    if (p_dev_rec->hci_handle == BTM_SEC_INVALID_HANDLE)
        return(btm_sec_dd_create_conn (p_dev_rec));

    /* If any security is required, get the name first */
    if (!(p_dev_rec->sec_flags & BTM_SEC_NAME_KNOWN)
        && (p_dev_rec->hci_handle != BTM_SEC_INVALID_HANDLE))
    {
        BTM_TRACE_EVENT0 ("Security Manager: Start get name");
        if (btm_sec_start_get_name (p_dev_rec))
            return(BTM_CMD_STARTED);

        p_dev_rec->sec_flags |= BTM_SEC_NAME_KNOWN;
    }

    /* If connection is not authenticated and authentication is required */
    /* start authentication and return PENDING to the caller */
    if ((!(p_dev_rec->sec_flags & BTM_SEC_AUTHENTICATED))
        && (( p_dev_rec->is_originator && (p_dev_rec->security_required & BTM_SEC_OUT_AUTHENTICATE))
            || (!p_dev_rec->is_originator && (p_dev_rec->security_required & BTM_SEC_IN_AUTHENTICATE)))
        && (p_dev_rec->hci_handle != BTM_SEC_INVALID_HANDLE))
    {
        BTM_TRACE_EVENT0 ("Security Manager: Start authentication");

        if (!btm_sec_start_authentication (p_dev_rec))
            return(BTM_NO_RESOURCES);
        return(BTM_CMD_STARTED);
    }

    /* If connection is not encrypted and encryption is required */
    /* start encryption and return PENDING to the caller */
    if (!(p_dev_rec->sec_flags & BTM_SEC_ENCRYPTED)
        && (( p_dev_rec->is_originator && (p_dev_rec->security_required & BTM_SEC_OUT_ENCRYPT))
            || (!p_dev_rec->is_originator && (p_dev_rec->security_required & BTM_SEC_IN_ENCRYPT)))
        && (p_dev_rec->hci_handle != BTM_SEC_INVALID_HANDLE))
    {
        BTM_TRACE_EVENT0 ("Security Manager: Start encryption");

        if (!btm_sec_start_encryption (p_dev_rec))
            return(BTM_NO_RESOURCES);
        return(BTM_CMD_STARTED);
    }

    /* If connection is not authorized and authorization is required */
    /* start authorization and return PENDING to the caller */
    if (!(p_dev_rec->sec_flags & BTM_SEC_AUTHORIZED)
        && (( p_dev_rec->is_originator && (p_dev_rec->security_required & BTM_SEC_OUT_AUTHORIZE))
            || (!p_dev_rec->is_originator && (p_dev_rec->security_required & BTM_SEC_IN_AUTHORIZE))))
    {
        if ((btm_sec_are_all_trusted(p_dev_rec->trusted_mask) == FALSE)
            && (p_dev_rec->p_cur_service->service_id < BTM_WII_SEC_MAX_SERVICES)
            && (BTM_SEC_IS_SERVICE_TRUSTED(p_dev_rec->trusted_mask,
                                           p_dev_rec->p_cur_service->service_id) == FALSE))
        {
            BTM_TRACE_EVENT0 ("Security Manager: Start authorization");
            return(btm_sec_start_authorization (p_dev_rec));
        }
    }

    /* All required  security procedures already established */
    p_dev_rec->security_required &= ~(BTM_SEC_OUT_AUTHORIZE | BTM_SEC_IN_AUTHORIZE |
                                      BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_IN_AUTHENTICATE |
                                      BTM_SEC_OUT_ENCRYPT | BTM_SEC_IN_ENCRYPT);

    BTM_TRACE_EVENT2 ("Security Manager: trusted:0x%04x%04x", p_dev_rec->trusted_mask[1], p_dev_rec->trusted_mask[0]);
    BTM_TRACE_EVENT0 ("Security Manager: access granted");

    return(BTM_SUCCESS);
}

/*******************************************************************************
**
** Function         btm_sec_start_authorization
**
*******************************************************************************/
UINT8 btm_sec_start_authorization (tBTM_SEC_DEV_REC *p_dev_rec)
{
    UINT8    result;
    UINT8   *p_service_name = NULL;
    UINT8    service_id;

    if ((p_dev_rec->sec_flags & BTM_SEC_NAME_KNOWN)
        || (p_dev_rec->hci_handle == BTM_SEC_INVALID_HANDLE))
    {
        if (!btm_cb.api.p_authorize_callback)
            return(BTM_MODE_UNSUPPORTED);

        if (p_dev_rec->p_cur_service)
        {
            if (p_dev_rec->is_originator)
                p_service_name = p_dev_rec->p_cur_service->orig_service_name;
            else
                p_service_name = p_dev_rec->p_cur_service->term_service_name;
            service_id = p_dev_rec->p_cur_service->service_id;
        }
        else
            service_id = 0;

        p_dev_rec->sec_state = BTM_SEC_STATE_AUTHORIZING;
        result = (*btm_cb.api.p_authorize_callback) (p_dev_rec->bd_addr,
                                                     p_dev_rec->dev_class,
                                                     p_dev_rec->sec_bd_name,
                                                     p_service_name,
                                                     service_id,
                                                     p_dev_rec->is_originator);
        if (result == BTM_SUCCESS)
        {
            p_dev_rec->sec_flags |= BTM_SEC_AUTHORIZED;
            p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;
        }
        return(result);
    }
    btm_sec_start_get_name (p_dev_rec);
    return(BTM_CMD_STARTED);
}

/*******************************************************************************
**
** Function         btm_sec_collision_timeout
**
*******************************************************************************/
void btm_sec_collision_timeout (TIMER_LIST_ENT *p_tle)
{
    tBTM_STATUS status;

    BTM_TRACE_EVENT0 ("btm_sec_collision_timeout()");
    btm_cb.sec_collision_tle.param = 0;

    status = btm_sec_execute_procedure (btm_cb.p_collided_dev_rec);

    /* If result is pending reply from the user or from the device is pending */
    if (status != BTM_CMD_STARTED)
    {
        /* There is no next procedure or start of procedure failed, notify the waiting layer */
        if (btm_cb.p_collided_dev_rec->p_callback)
        {
            BTM_SEC_CLR_MX_CHAN(btm_cb.p_collided_dev_rec);
            (*btm_cb.p_collided_dev_rec->p_callback) (btm_cb.p_collided_dev_rec->bd_addr,
                                                      btm_cb.p_collided_dev_rec->p_ref_data, status);
            btm_cb.p_collided_dev_rec->p_callback = NULL;
        }
    }
}

/*******************************************************************************
**
** Function         BTM_ReadTrustedMask
**
*******************************************************************************/
UINT32 *BTM_ReadTrustedMask (BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev (bd_addr);
    if (p_dev_rec != NULL)
        return(p_dev_rec->trusted_mask);
    return NULL;
}
