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
 *  This file contains functions that handle inquiries. These include
 *  setting discoverable mode, controlling the mode of the Baseband, and
 *  maintaining a small database of inquiry responses, with API for people
 *  to browse it.
 *
 ******************************************************************************/

/* Wii (older BTE) structure layouts */
#define BTM_WII_LAYOUT
#define L2C_WII_LAYOUT
#define HCIC_WII_LAYOUT

/* Wii prototypes use the older (no EIR) inquiry types */
#define BTM_StartInquiry            BTM_StartInquiry_proto_unused
#define BTM_InqDbRead               BTM_InqDbRead_proto_unused
#define BTM_InqDbFirst              BTM_InqDbFirst_proto_unused
#define BTM_InqDbNext               BTM_InqDbNext_proto_unused
#define btm_initiate_rem_name       btm_initiate_rem_name_proto_unused
#define btm_process_inq_complete    btm_process_inq_complete_proto_unused
#define btm_inq_db_new              btm_inq_db_new_proto_unused
#define btm_inq_db_find             btm_inq_db_find_proto_unused
#define btsnd_hcic_set_event_filter btsnd_hcic_set_event_filter_proto_unused
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>

#include "bt_types.h"
#include "gki.h"
#include "hcimsgs.h"
#include "btu.h"
#include "btm_api.h"
#include "btm_int.h"
#include "hcidefs.h"
#undef BTM_StartInquiry
#undef BTM_InqDbRead
#undef BTM_InqDbFirst
#undef BTM_InqDbNext
#undef btm_initiate_rem_name
#undef btm_process_inq_complete
#undef btm_inq_db_new
#undef btm_inq_db_find
#undef btsnd_hcic_set_event_filter

/* Wii BTE (older build): bodies rewritten from the RSPE01_01 asm. */

#define BTM_WII_LIMITED_INQUIRY_ACTIVE  0x1
#define BTM_WII_GENERAL_INQUIRY_ACTIVE  0x2
#define BTM_WII_PERIODIC_INQUIRY_ACTIVE 0x4

#define BTM_WII_DEV_STATE_READY     3   /* inferred */
#define BTM_WII_MIN_SCAN_WINDOW     0x12 /* older hcidefs value */

#define BTM_INQ_INACTIVE_STATE      0
#define BTM_INQ_CLR_FILT_STATE      1
#define BTM_INQ_SET_FILT_STATE      2
#define BTM_INQ_ACTIVE_STATE        3

typedef tBTM_INQUIRY_VAR_ST_WII tBTM_INQ_VARS;
typedef void (tBTM_WII_INQ_RESULTS_CB) (tBTM_WII_INQ_RESULTS *p_inq_results);
typedef void (tBTM_WII_INQ_DB_CHANGE_CB) (tBTM_WII_INQ_INFO *p_info, BOOLEAN is_new);

/* Wii hcic commands take a caller-allocated command buffer */
extern BOOLEAN btsnd_hcic_write_cur_iac_lap (BT_HDR *p_buf, UINT8 num_cur_iac, LAP * const iac_lap);
extern BOOLEAN btsnd_hcic_write_inqscan_cfg (BT_HDR *p_buf, UINT16 interval, UINT16 window);
extern BOOLEAN btsnd_hcic_write_pagescan_cfg (BT_HDR *p_buf, UINT16 interval, UINT16 window);
extern BOOLEAN btsnd_hcic_write_scan_enable (BT_HDR *p_buf, UINT8 flag);
extern BOOLEAN btsnd_hcic_write_inqscan_type (BT_HDR *p_buf, UINT8 type);
extern BOOLEAN btsnd_hcic_write_pagescan_type (BT_HDR *p_buf, UINT8 type);
extern BOOLEAN btsnd_hcic_write_inquiry_mode (BT_HDR *p_buf, UINT8 mode);
extern BOOLEAN btsnd_hcic_set_event_filter (BT_HDR *p_buf, UINT8 filt_type, UINT8 filt_cond_type,
                                            UINT8 *filt_cond, UINT8 filt_cond_len);

tBTM_STATUS btm_initiate_rem_name (BD_ADDR remote_bda, tBTM_WII_INQ_INFO *p_cur,
                                   UINT8 origin, UINT32 timeout, tBTM_CMPL_CB *p_cb);
void btm_process_inq_complete (UINT8 status);
tINQ_DB_ENT_WII *btm_inq_db_new (BD_ADDR p_bda);
tBTM_STATUS btm_set_inq_event_filter (UINT8 filter_cond_type, tBTM_INQ_FILT_COND *p_filt_cond);
tBTM_WII_INQ_INFO *BTM_InqDbFirst (void);

static const LAP general_inq_lap = {0x9e,0x8b,0x33};
static const LAP limited_inq_lap = {0x9e,0x8b,0x00};

/*******************************************************************************
** Inlined helpers
*******************************************************************************/
static tINQ_DB_ENT_WII *btm_inq_db_find (BD_ADDR p_bda)
{
    UINT16       xx;
    tINQ_DB_ENT_WII *p_ent = btm_cb.btm_inq_vars.inq_db;

    for (xx = 0; xx < BTM_WII_INQ_DB_SIZE; xx++, p_ent++)
    {
        if ((p_ent->in_use) && (!memcmp (p_ent->inq_info.results.remote_bd_addr, p_bda, BD_ADDR_LEN)))
            return (p_ent);
    }

    return (NULL);
}

static void btm_clr_inq_db (BD_ADDR p_bda)
{
    tINQ_DB_ENT_WII *p_ent = btm_cb.btm_inq_vars.inq_db;
    UINT16           xx;

    for (xx = 0; xx < BTM_WII_INQ_DB_SIZE; xx++, p_ent++)
    {
        if (p_ent->in_use)
        {
            if (p_bda == NULL || (!memcmp (p_ent->inq_info.results.remote_bd_addr, p_bda, BD_ADDR_LEN)))
            {
                p_ent->in_use = FALSE;

                if (btm_cb.btm_inq_vars.p_inq_change_cb)
                    (*(tBTM_WII_INQ_DB_CHANGE_CB *)btm_cb.btm_inq_vars.p_inq_change_cb)(&p_ent->inq_info, FALSE);
            }
        }
    }
}

static void btm_clr_inq_result_flt (void)
{
    tBTM_INQ_VARS *p_inq = &btm_cb.btm_inq_vars;

    if (p_inq->p_bd_db)
    {
        GKI_freebuf(p_inq->p_bd_db);
        p_inq->p_bd_db = NULL;
    }
    p_inq->num_bd_entries = 0;
    p_inq->max_bd_entries = 0;
}

static void btm_initiate_inquiry (tBTM_INQ_VARS *p_inq)
{
    const LAP          *lap;
    tBTM_WII_INQ_PARMS *p_inqparms = &p_inq->inqparms;

    p_inqparms->max_resps = (p_inqparms->max_resps > BTM_WII_INQ_DB_SIZE) ?
                            BTM_WII_INQ_DB_SIZE : p_inqparms->max_resps;

    lap = (p_inq->inq_active & BTM_WII_LIMITED_INQUIRY_ACTIVE) ? &limited_inq_lap : &general_inq_lap;

    if (p_inq->inq_active & BTM_WII_PERIODIC_INQUIRY_ACTIVE)
    {
        if (!btsnd_hcic_per_inq_mode (p_inq->per_max_delay,
                                      p_inq->per_min_delay,
                                      *lap, p_inqparms->duration,
                                      p_inqparms->max_resps))
            btm_process_inq_complete (BTM_NO_RESOURCES);
    }
    else
    {
        btm_clr_inq_result_flt();

        if ((p_inq->p_bd_db = (tINQ_BDADDR *)GKI_getbuf(GKI_MAX_BUF_SIZE)) != NULL)
        {
            p_inq->max_bd_entries = (UINT16)(GKI_MAX_BUF_SIZE / sizeof(tINQ_BDADDR));
            memset(p_inq->p_bd_db, 0, GKI_MAX_BUF_SIZE);
        }

        if (!btsnd_hcic_inquiry(*lap, p_inqparms->duration, 0))
            btm_process_inq_complete (BTM_NO_RESOURCES);
    }
}

/*******************************************************************************
**
** Function         BTM_SetDiscoverability
**
*******************************************************************************/
tBTM_STATUS BTM_SetDiscoverability (UINT16 inq_mode, UINT16 window, UINT16 interval)
{
    UINT8        scan_mode = 0;
    UINT16       service_class;
    UINT8       *p_cod;
    UINT8        major, minor;
    DEV_CLASS    cod;
    LAP          temp_lap[2];
    BOOLEAN      is_limited;
    BOOLEAN      cod_limited;
    BT_HDR      *p_buf;

    /*** Check mode parameter ***/
    if (inq_mode != BTM_NON_DISCOVERABLE && inq_mode != BTM_LIMITED_DISCOVERABLE &&
        inq_mode != BTM_GENERAL_DISCOVERABLE)
        return (BTM_ILLEGAL_VALUE);

    /* Make sure the controller is active */
    if (btm_cb.devcb.state < BTM_WII_DEV_STATE_READY)
        return (BTM_DEV_RESET);

    /* If the window and/or interval is '0', set to default values */
    if (!window)
        window = BTM_DEFAULT_DISC_WINDOW;

    if (!interval)
        interval = BTM_DEFAULT_DISC_INTERVAL;

    BTM_TRACE_API3 ("BTM_SetDiscoverability: mode %d [NonDisc-0, Lim-1, Gen-2], window 0x%04x, interval 0x%04x",
                        inq_mode, window, interval);

    /*** Check for valid window and interval parameters ***/
    /*** Only check window and duration if mode is connectable ***/
    if (inq_mode != BTM_NON_DISCOVERABLE)
    {
        /* window must be less than or equal to interval */
        if (window < BTM_WII_MIN_SCAN_WINDOW        ||
            window > HCI_MAX_INQUIRYSCAN_WINDOW     ||
            interval < HCI_MIN_INQUIRYSCAN_INTERVAL ||
            interval > HCI_MAX_INQUIRYSCAN_INTERVAL ||
            window > interval)
        {
            return (BTM_ILLEGAL_VALUE);
        }
    }

    /* Set the IAC if needed */
    if (inq_mode != BTM_NON_DISCOVERABLE)
    {
        if ((p_buf = HCI_GET_CMD_BUF(0)) != NULL)
        {
            if (inq_mode & BTM_LIMITED_DISCOVERABLE)
            {
                /* Use the GIAC and LIAC codes for limited discoverable mode */
                memcpy (temp_lap[0], limited_inq_lap, LAP_LEN);
                memcpy (temp_lap[1], general_inq_lap, LAP_LEN);

                btsnd_hcic_write_cur_iac_lap (p_buf, 2, (LAP * const) temp_lap);
            }
            else
            {
                btsnd_hcic_write_cur_iac_lap (p_buf, 1, (LAP * const) &general_inq_lap);
            }

            scan_mode |= HCI_INQUIRY_SCAN_ENABLED;
        }
        else
            return (BTM_NO_RESOURCES);  /* Cannot continue */
    }

    /* Send down the inquiry scan window and period if changed */
    if ((window != btm_cb.btm_inq_vars.inq_scan_window) ||
        (interval != btm_cb.btm_inq_vars.inq_scan_period))
    {
        if ((p_buf = HCI_GET_CMD_BUF(0)) != NULL)
        {
            btm_cb.btm_inq_vars.inq_scan_window = window;
            btm_cb.btm_inq_vars.inq_scan_period = interval;
            btsnd_hcic_write_inqscan_cfg (p_buf, interval, window);
        }
        else
            return (BTM_NO_RESOURCES);
    }

    if ((p_buf = HCI_GET_CMD_BUF(0)) != NULL)
    {
        if (btm_cb.btm_inq_vars.connectable_mode)
            scan_mode |= HCI_PAGE_SCAN_ENABLED;

        btm_cb.btm_inq_vars.discoverable_mode = inq_mode;
        btsnd_hcic_write_scan_enable (p_buf, scan_mode);
    }
    else
        return (BTM_NO_RESOURCES);

    /* Change the service class bit if mode has changed */
    p_cod = BTM_ReadDeviceClass();
    BTM_COD_SERVICE_CLASS(service_class, p_cod);
    is_limited = (inq_mode & BTM_LIMITED_DISCOVERABLE) ? TRUE : FALSE;
    cod_limited = (service_class & BTM_COD_SERVICE_LMTD_DISCOVER) ? TRUE : FALSE;
    if (is_limited ^ cod_limited)
    {
        BTM_COD_MINOR_CLASS(minor, p_cod );
        BTM_COD_MAJOR_CLASS(major, p_cod );
        if (is_limited)
            service_class |= BTM_COD_SERVICE_LMTD_DISCOVER;
        else
            service_class &= ~BTM_COD_SERVICE_LMTD_DISCOVER;

        FIELDS_TO_COD(cod, minor, major, service_class);
        (void) BTM_SetDeviceClass (cod);
    }

    return (BTM_SUCCESS);
}

/*******************************************************************************
**
** Function         BTM_SetInquiryScanType
**
*******************************************************************************/
tBTM_STATUS BTM_SetInquiryScanType (UINT16 scan_type)
{
    BT_HDR *p_buf;

    if (scan_type != BTM_SCAN_TYPE_STANDARD && scan_type != BTM_SCAN_TYPE_INTERLACED)
        return (BTM_ILLEGAL_VALUE);

    /* whatever app wants if device is not 1.2 scan type should be STANDARD */
    if (!HCI_LMP_INTERLACED_INQ_SCAN_SUPPORTED(btm_cb.devcb.local_features))
        return (BTM_MODE_UNSUPPORTED);

    /* Check for scan type if configuration has been changed */
    if (scan_type != btm_cb.btm_inq_vars.inq_scan_type)
    {
        if (BTM_IsDeviceUp())
        {
            if ((p_buf = HCI_GET_CMD_BUF(0)) != NULL)
            {
                btsnd_hcic_write_inqscan_type (p_buf, (UINT8)scan_type);
                btm_cb.btm_inq_vars.inq_scan_type = scan_type;
            }
            else
                return (BTM_NO_RESOURCES);
        }
        else return (BTM_WRONG_MODE);
    }
    return (BTM_SUCCESS);
}

/*******************************************************************************
**
** Function         BTM_SetPageScanType
**
*******************************************************************************/
tBTM_STATUS BTM_SetPageScanType (UINT16 scan_type)
{
    BT_HDR *p_buf;

    if (scan_type != BTM_SCAN_TYPE_STANDARD && scan_type != BTM_SCAN_TYPE_INTERLACED)
        return (BTM_ILLEGAL_VALUE);

    /* whatever app wants if device is not 1.2 scan type should be STANDARD */
    if (!HCI_LMP_INTERLACED_PAGE_SCAN_SUPPORTED(btm_cb.devcb.local_features))
        return (BTM_MODE_UNSUPPORTED);

    /* Check for scan type if configuration has been changed */
    if (scan_type != btm_cb.btm_inq_vars.page_scan_type)
    {
        if (BTM_IsDeviceUp())
        {
            if ((p_buf = HCI_GET_CMD_BUF(0)) != NULL)
            {
                btsnd_hcic_write_pagescan_type (p_buf, (UINT8)scan_type);
                btm_cb.btm_inq_vars.page_scan_type = scan_type;
            }
            else
                return (BTM_NO_RESOURCES);
        }
        else return (BTM_WRONG_MODE);
    }
    return (BTM_SUCCESS);
}

/*******************************************************************************
**
** Function         BTM_SetInquiryMode
**
*******************************************************************************/
tBTM_STATUS BTM_SetInquiryMode (UINT8 mode)
{
    BT_HDR *p_buf;

    if (mode != BTM_INQ_RESULT_STANDARD && mode != BTM_INQ_RESULT_WITH_RSSI)
        return (BTM_ILLEGAL_VALUE);

    if (!HCI_LMP_INQ_RSSI_SUPPORTED(btm_cb.devcb.local_features))
        return (BTM_MODE_UNSUPPORTED);

    if (!BTM_IsDeviceUp())
        return (BTM_WRONG_MODE);

    if ((p_buf = HCI_GET_CMD_BUF(0)) != NULL)
        btsnd_hcic_write_inquiry_mode (p_buf, mode);
    else
        return (BTM_NO_RESOURCES);

    return (BTM_SUCCESS);
}

/*******************************************************************************
**
** Function         BTM_SetConnectability
**
*******************************************************************************/
tBTM_STATUS BTM_SetConnectability (UINT16 page_mode, UINT16 window, UINT16 interval)
{
    UINT8    scan_mode = 0;
    tBTM_INQ_VARS *p_inq = &btm_cb.btm_inq_vars;
    BT_HDR  *p_buf;

    /*** Check mode parameter ***/
    if (page_mode != BTM_NON_CONNECTABLE && page_mode != BTM_CONNECTABLE)
        return (BTM_ILLEGAL_VALUE);

    /* Make sure the controller is active */
    if (btm_cb.devcb.state < BTM_WII_DEV_STATE_READY)
        return (BTM_DEV_RESET);

    /* If the window and/or interval is '0', set to default values */
    if (!window)
        window = BTM_DEFAULT_CONN_WINDOW;

    if (!interval)
        interval = BTM_DEFAULT_CONN_INTERVAL;

    BTM_TRACE_API3 ("BTM_SetConnectability: mode %d [NonConn-0, Conn-1], window 0x%04x, interval 0x%04x",
                        page_mode, window, interval);

    /*** Check for valid window and interval parameters ***/
    /*** Only check window and duration if mode is connectable ***/
    if (page_mode == BTM_CONNECTABLE)
    {
        /* window must be less than or equal to interval */
        if (window < BTM_WII_MIN_SCAN_WINDOW     ||
            window > HCI_MAX_PAGESCAN_WINDOW     ||
            interval < HCI_MIN_PAGESCAN_INTERVAL ||
            interval > HCI_MAX_PAGESCAN_INTERVAL ||
            window > interval)
        {
            return (BTM_ILLEGAL_VALUE);
        }

        scan_mode |= HCI_PAGE_SCAN_ENABLED;
    }

    if ((window != p_inq->page_scan_window) ||
        (interval != p_inq->page_scan_period))
    {
        if ((p_buf = HCI_GET_CMD_BUF(0)) != NULL)
        {
            p_inq->page_scan_window = window;
            p_inq->page_scan_period = interval;
            btsnd_hcic_write_pagescan_cfg (p_buf, interval, window);
        }
        else
            return (BTM_NO_RESOURCES);
    }

    if ((p_buf = HCI_GET_CMD_BUF(0)) != NULL)
    {
        /* Keep the inquiry scan as previouosly set */
        if (p_inq->discoverable_mode)
            scan_mode |= HCI_INQUIRY_SCAN_ENABLED;

        p_inq->connectable_mode = page_mode;
        btsnd_hcic_write_scan_enable (p_buf, scan_mode);
    }
    else
        return (BTM_NO_RESOURCES);

    return (BTM_SUCCESS);
}

/*******************************************************************************
**
** Function         BTM_IsInquiryActive
**
*******************************************************************************/
UINT16 BTM_IsInquiryActive (void)
{
    return(btm_cb.btm_inq_vars.inq_active);
}

/*******************************************************************************
**
** Function         BTM_CancelInquiry
**
*******************************************************************************/
tBTM_STATUS BTM_CancelInquiry(void)
{
    tBTM_STATUS           status = BTM_SUCCESS;
    tBTM_INQ_VARS        *p_inq = &btm_cb.btm_inq_vars;

    BTM_TRACE_API0 ("BTM_CancelInquiry called");

    /*** Make sure the device is ready ***/
    if (!BTM_IsDeviceUp())
        return (BTM_WRONG_MODE);

    /* Only cancel if not in periodic mode, otherwise the caller should call BTM_CancelPeriodicMode */
    if (p_inq->inq_active && !(p_inq->inq_active & BTM_WII_PERIODIC_INQUIRY_ACTIVE))
    {
        p_inq->inq_active = BTM_INQUIRY_INACTIVE;
        p_inq->state = BTM_INQ_INACTIVE_STATE;
        p_inq->p_inq_results_cb = (tBTM_INQ_RESULTS_CB *) NULL; /* Do not notify caller anymore */
        p_inq->p_inq_cmpl_cb = (tBTM_CMPL_CB *) NULL;    /* Do not notify caller anymore */

        /* If the event filter is in progress, mark it so that the processing of the return
            event will be ignored */
        if (p_inq->inqfilt_active)
        {
            p_inq->inqfilt_active = FALSE;
            p_inq->pending_filt_complete_event++;
        }
        /* Initiate the cancel inquiry */
        else
        {
            if (!btsnd_hcic_inq_cancel())
                status = BTM_NO_RESOURCES;
        }

        p_inq->inq_counter++;
        btm_clr_inq_result_flt();
    }

    return (status);
}

/*******************************************************************************
**
** Function         BTM_StartInquiry
**
*******************************************************************************/
tBTM_STATUS BTM_StartInquiry (tBTM_WII_INQ_PARMS *p_inqparms, tBTM_INQ_RESULTS_CB *p_results_cb,
                              tBTM_CMPL_CB *p_cmpl_cb)
{
    tBTM_STATUS    status;
    tBTM_INQ_VARS *p_inq = &btm_cb.btm_inq_vars;

    BTM_TRACE_API4 ("BTM_StartInquiry: mode: %d, dur: %d, rsps: %d, flt: %d",
                        p_inqparms->mode, p_inqparms->duration, p_inqparms->max_resps,
                        p_inqparms->filter_cond_type);

    /* Only one active inquiry is allowed in this implementation.
       Also do not allow an inquiry if the inquiry filter is being updated */
    if (p_inq->inq_active || p_inq->inqfilt_active)
        return (BTM_BUSY);

    /*** Make sure the device is ready ***/
    if (p_inqparms->mode != BTM_GENERAL_INQUIRY &&
        p_inqparms->mode != BTM_LIMITED_INQUIRY)
        return (BTM_ILLEGAL_VALUE);

    if (!BTM_IsDeviceUp())
        return (BTM_WRONG_MODE);

    /* Save the inquiry parameters to be used upon the completion of setting/clearing the inquiry filter */
    p_inq->inqparms = *p_inqparms;
    p_inq->state = BTM_INQ_ACTIVE_STATE;

    /* Initialize the inquiry variables */
    p_inq->p_inq_cmpl_cb = p_cmpl_cb;
    p_inq->p_inq_results_cb = p_results_cb;
    p_inq->inq_cmpl_info.num_resp = 0;         /* Clear the results counter */
    p_inq->inq_active = (p_inqparms->mode == BTM_LIMITED_INQUIRY) ?
                        BTM_WII_LIMITED_INQUIRY_ACTIVE : BTM_WII_GENERAL_INQUIRY_ACTIVE;

    switch (p_inqparms->filter_cond_type)
    {
    case BTM_CLR_INQUIRY_FILTER:
        p_inq->state = BTM_INQ_SET_FILT_STATE;
        break;

    case BTM_FILTER_COND_DEVICE_CLASS:
    case BTM_FILTER_COND_BD_ADDR:
        /* The filter is not being used so simply clear it;
            the inquiry can start after this operation */
        p_inq->state = BTM_INQ_CLR_FILT_STATE;
        p_inqparms->filter_cond_type = BTM_CLR_INQUIRY_FILTER;
        break;

    default:
        return (BTM_ILLEGAL_VALUE);
    }

    /* Before beginning the inquiry the current filter must be cleared, so initiate the command */
    if ((status = btm_set_inq_event_filter (p_inqparms->filter_cond_type, &p_inqparms->filter_cond)) != BTM_CMD_STARTED)
        p_inq->state = BTM_INQ_INACTIVE_STATE;

    return (status);
}

/*******************************************************************************
**
** Function         BTM_ReadRemoteDeviceName
**
*******************************************************************************/
tBTM_STATUS  BTM_ReadRemoteDeviceName (BD_ADDR remote_bda, tBTM_CMPL_CB *p_cb)
{
    tBTM_WII_INQ_INFO *p_cur = NULL;
    tINQ_DB_ENT_WII   *p_i;

    BTM_TRACE_API6 ("BTM_ReadRemoteDeviceName: bd addr [%02x%02x%02x%02x%02x%02x]",
               remote_bda[0], remote_bda[1], remote_bda[2],
               remote_bda[3], remote_bda[4], remote_bda[5]);

    /* Use the remote device's clock offset if it is in the local inquiry database */
    if ((p_i = btm_inq_db_find (remote_bda)) != NULL)
    {
        p_cur = &p_i->inq_info;
    }

    return (btm_initiate_rem_name (remote_bda, p_cur, BTM_RMT_NAME_EXT,
                                   BTM_EXT_RMT_NAME_TIMEOUT, p_cb));
}

/*******************************************************************************
**
** Function         BTM_CancelRemoteDeviceName
**
*******************************************************************************/
tBTM_STATUS  BTM_CancelRemoteDeviceName (void)
{
    tBTM_INQ_VARS *p_inq = &btm_cb.btm_inq_vars;

    BTM_TRACE_API0 ("BTM_CancelRemoteDeviceName()");

    /* Make sure there is not already one in progress */
    if (p_inq->remname_active & BTM_RMT_NAME_EXT)
    {
        if (btsnd_hcic_rmt_name_req_cancel (p_inq->remname_bda))
            return (BTM_CMD_STARTED);
        else
            return (BTM_NO_RESOURCES);
    }
    else
        return (BTM_WRONG_MODE);
}

/*******************************************************************************
**
** Function         BTM_InqDbRead
**
*******************************************************************************/
tBTM_WII_INQ_INFO *BTM_InqDbRead (BD_ADDR p_bda)
{
    UINT16       xx;
    tINQ_DB_ENT_WII *p_ent = btm_cb.btm_inq_vars.inq_db;

    BTM_TRACE_API6 ("BTM_InqDbRead: bd addr [%02x%02x%02x%02x%02x%02x]",
               p_bda[0], p_bda[1], p_bda[2], p_bda[3], p_bda[4], p_bda[5]);

    for (xx = 0; xx < BTM_WII_INQ_DB_SIZE; xx++, p_ent++)
    {
        if ((p_ent->in_use) && (!memcmp (p_ent->inq_info.results.remote_bd_addr, p_bda, BD_ADDR_LEN)))
            return (&p_ent->inq_info);
    }

    /* If here, not found */
    return ((tBTM_WII_INQ_INFO *)NULL);
}

/*******************************************************************************
**
** Function         BTM_InqDbFirst
**
*******************************************************************************/
tBTM_WII_INQ_INFO *BTM_InqDbFirst (void)
{
    UINT16       xx;
    tINQ_DB_ENT_WII *p_ent = btm_cb.btm_inq_vars.inq_db;

    for (xx = 0; xx < BTM_WII_INQ_DB_SIZE; xx++, p_ent++)
    {
        if (p_ent->in_use)
            return (&p_ent->inq_info);
    }

    /* If here, no used entry found */
    return ((tBTM_WII_INQ_INFO *)NULL);
}

/*******************************************************************************
**
** Function         BTM_InqDbNext
**
*******************************************************************************/
tBTM_WII_INQ_INFO *BTM_InqDbNext (tBTM_WII_INQ_INFO *p_cur)
{
    tINQ_DB_ENT_WII *p_ent;
    UINT16       inx;

    if (p_cur)
    {
        p_ent = (tINQ_DB_ENT_WII *) ((UINT8 *) p_cur - offsetof (tINQ_DB_ENT_WII, inq_info));
        inx = (UINT16)((p_ent - btm_cb.btm_inq_vars.inq_db) + 1);

        for (p_ent = &btm_cb.btm_inq_vars.inq_db[inx]; inx < BTM_WII_INQ_DB_SIZE; inx++, p_ent++)
        {
            if (p_ent->in_use)
                return (&p_ent->inq_info);
        }

        /* If here, more entries found */
        return ((tBTM_WII_INQ_INFO *)NULL);
    }
    else
        return (BTM_InqDbFirst());
}

/*******************************************************************************
**
** Function         BTM_ClearInqDb
**
*******************************************************************************/
tBTM_STATUS BTM_ClearInqDb (BD_ADDR p_bda)
{
    /* If an inquiry or remote name is in progress return busy */
    if (btm_cb.btm_inq_vars.inq_active != BTM_INQUIRY_INACTIVE ||
        btm_cb.btm_inq_vars.remname_active ||
        btm_cb.btm_inq_vars.inqfilt_active)
        return (BTM_BUSY);

    btm_clr_inq_db(p_bda);

    return (BTM_SUCCESS);
}

/*******************************************************************************
**
** Function         btm_inq_db_reset
**
*******************************************************************************/
void btm_inq_db_reset (void)
{
    tBTM_REMOTE_DEV_NAME     rem_name;
    tBTM_INQ_VARS           *p_inq = &btm_cb.btm_inq_vars;
    UINT8                    num_responses;
    UINT8                    temp_inq_active;
    tBTM_STATUS              status;

    btu_stop_timer (&p_inq->inq_timer_ent);

    /* If an inquiry or periodic inquiry is active, reset the mode to inactive */
    if (p_inq->inq_active != BTM_INQUIRY_INACTIVE)
    {
        temp_inq_active = p_inq->inq_active;    /* Save so state can change BEFORE
                                                       callback is called */
        p_inq->inq_active = BTM_INQUIRY_INACTIVE;

        /* If not a periodic inquiry, the complete callback must be called to notify caller */
        if (temp_inq_active == BTM_WII_LIMITED_INQUIRY_ACTIVE ||
            temp_inq_active == BTM_WII_GENERAL_INQUIRY_ACTIVE)
        {
            if (p_inq->p_inq_cmpl_cb)
            {
                num_responses = 0;
                (*p_inq->p_inq_cmpl_cb)(&num_responses);
            }
        }
    }

    /* Cancel a remote name request if active, and notify the caller (if waiting) */
    if (p_inq->remname_active & BTM_RMT_NAME_EXT)
    {
        btu_stop_timer (&p_inq->rmt_name_timer_ent);
        p_inq->remname_active = FALSE;
        memset(p_inq->remname_bda, 0, BD_ADDR_LEN);

        if (p_inq->p_remname_cmpl_cb)
        {
            rem_name.status = BTM_DEV_RESET;

            (*p_inq->p_remname_cmpl_cb)(&rem_name);
            p_inq->p_remname_cmpl_cb = NULL;
        }
    }

    /* Cancel an inquiry filter request if active, and notify the caller (if waiting) */
    if (p_inq->inqfilt_active)
    {
        p_inq->inqfilt_active = FALSE;

        if (p_inq->p_inqfilter_cmpl_cb)
        {
            status = BTM_DEV_RESET;
            (*p_inq->p_inqfilter_cmpl_cb)(&status);
        }
    }

    p_inq->state = BTM_INQ_INACTIVE_STATE;
    p_inq->pending_filt_complete_event = 0;
    p_inq->p_inq_results_cb = NULL;
    btm_clr_inq_db(NULL);   /* Clear out all the entries in the database */
    btm_clr_inq_result_flt();

    p_inq->discoverable_mode = BTM_NON_DISCOVERABLE;
    p_inq->connectable_mode  = BTM_NON_CONNECTABLE;
    p_inq->page_scan_type    = BTM_SCAN_TYPE_STANDARD;
    p_inq->inq_scan_type     = BTM_SCAN_TYPE_STANDARD;
}

/*********************************************************************************
**
** Function         btm_inq_db_init
**
**********************************************************************************/
void btm_inq_db_init (void)
{
}

/*******************************************************************************
**
** Function         btm_inq_find_bdaddr
**
*******************************************************************************/
BOOLEAN btm_inq_find_bdaddr (BD_ADDR p_bda)
{
    tBTM_INQ_VARS *p_inq = &btm_cb.btm_inq_vars;
    tINQ_BDADDR   *p_db = &p_inq->p_bd_db[0];
    UINT16       xx;

    /* Don't bother searching, database doesn't exist or periodic mode */
    if ((p_inq->inq_active & BTM_WII_PERIODIC_INQUIRY_ACTIVE) || !p_db)
        return (FALSE);

    for (xx = 0; xx < p_inq->num_bd_entries; xx++, p_db++)
    {
        if (!memcmp(p_db->bd_addr, p_bda, BD_ADDR_LEN)
            && p_db->inq_count == p_inq->inq_counter)
            return (TRUE);
    }

    if (xx < p_inq->max_bd_entries)
    {
        p_db->inq_count = p_inq->inq_counter;
        memcpy(p_db->bd_addr, p_bda, BD_ADDR_LEN);
        p_inq->num_bd_entries++;
    }

    /* If here, New device */
    return (FALSE);
}

/*******************************************************************************
**
** Function         btm_inq_db_new
**
*******************************************************************************/
tINQ_DB_ENT_WII *btm_inq_db_new (BD_ADDR p_bda)
{
    UINT16       xx;
    tINQ_DB_ENT_WII *p_ent = btm_cb.btm_inq_vars.inq_db;
    tINQ_DB_ENT_WII *p_old = btm_cb.btm_inq_vars.inq_db;
    UINT32       ot = 0xFFFFFFFF;

    for (xx = 0; xx < BTM_WII_INQ_DB_SIZE; xx++, p_ent++)
    {
        if (!p_ent->in_use)
        {
            memset (p_ent, 0, sizeof (tINQ_DB_ENT_WII));
            memcpy (p_ent->inq_info.results.remote_bd_addr, p_bda, BD_ADDR_LEN);
            p_ent->in_use = TRUE;

            return (p_ent);
        }

        if (p_ent->time_of_resp < ot)
        {
            p_old = p_ent;
            ot    = p_ent->time_of_resp;
        }
    }

    /* If here, no free entry found. Return the oldest. */

    /* Before deleting the oldest, if anyone is registered for change */
    /* notifications, then tell him we are deleting an entry.        */
    if (btm_cb.btm_inq_vars.p_inq_change_cb)
        (*(tBTM_WII_INQ_DB_CHANGE_CB *)btm_cb.btm_inq_vars.p_inq_change_cb)(&p_old->inq_info, FALSE);

    memset (p_old, 0, sizeof (tINQ_DB_ENT_WII));
    memcpy (p_old->inq_info.results.remote_bd_addr, p_bda, BD_ADDR_LEN);
    p_old->in_use = TRUE;

    return (p_old);
}

/*******************************************************************************
**
** Function         btm_set_inq_event_filter
**
*******************************************************************************/
tBTM_STATUS btm_set_inq_event_filter (UINT8 filter_cond_type,
                                      tBTM_INQ_FILT_COND *p_filt_cond)
{
    BT_HDR  *p_buf;
    UINT8    condition_length = DEV_CLASS_LEN * 2;
    UINT8    condition_buf[DEV_CLASS_LEN * 2];
    UINT8   *p_cond = condition_buf;                    /* points to the condition to pass to HCI */

    if ((p_buf = HCI_GET_CMD_BUF(0)) != NULL)
    {
        /* Load the correct filter condition to pass to the lower layer */
        switch (filter_cond_type)
        {
        case BTM_FILTER_COND_DEVICE_CLASS:
            /* copy the device class and device class fields into contiguous memory to send to HCI */
            memcpy (condition_buf, p_filt_cond->cod_cond.dev_class, DEV_CLASS_LEN);
            memcpy (&condition_buf[DEV_CLASS_LEN],
                    p_filt_cond->cod_cond.dev_class_mask, DEV_CLASS_LEN);
            break;

        case BTM_FILTER_COND_BD_ADDR:
            p_cond = p_filt_cond->bdaddr_cond;
            break;

        case BTM_CLR_INQUIRY_FILTER:
            condition_length = 0;
            break;

        default:
            return (BTM_ILLEGAL_VALUE);     /* Bad parameter was passed in */
        }

        btm_cb.btm_inq_vars.inqfilt_active = TRUE;

        /* Filter the inquiry results for the specified condition type and value */
        btsnd_hcic_set_event_filter(p_buf, HCI_FILTER_INQUIRY_RESULT, filter_cond_type,
                                    p_cond, condition_length);
        return (BTM_CMD_STARTED);
    }
    else
        return (BTM_NO_RESOURCES);
}

/*******************************************************************************
**
** Function         btm_event_filter_complete
**
*******************************************************************************/
void btm_event_filter_complete (UINT8 *p)
{
    UINT8            hci_status;
    tBTM_STATUS      status;
    tBTM_INQ_VARS   *p_inq = &btm_cb.btm_inq_vars;
    tBTM_CMPL_CB    *p_cb = p_inq->p_inqfilter_cmpl_cb;

    /* If the filter complete event is from an old or cancelled request, ignore it */
    if(p_inq->pending_filt_complete_event)
    {
        p_inq->pending_filt_complete_event--;
        return;
    }

    /* Only process the inquiry filter; Ignore the connection filter until it
       is used by the upper layers */
    if (p_inq->inqfilt_active == TRUE )
    {
        /* Extract the returned status from the buffer */
        STREAM_TO_UINT8 (hci_status, p);
        if (hci_status != HCI_SUCCESS)
        {
            /* If standalone filter command, return the error status */
            BTM_TRACE_WARNING1 ("BTM Warning: Set Event Filter Failed (HCI returned 0x%x)", hci_status);
            status = BTM_ERR_PROCESSING;
        }
        else
            status = BTM_SUCCESS;

        /* If the set filter was initiated externally (via BTM_SetInqEventFilter),
           call the callback function to notify the caller that it has completed */
        if (p_inq->state == BTM_INQ_INACTIVE_STATE)
        {
            p_inq->inqfilt_active = FALSE;
            if (p_cb)
                (*p_cb) (&status);
        }
        else    /* An inquiry is active (the set filter command was internally generated),
                   process the next state of the process (Set a new filter or start the inquiry). */
        {
            if(status != BTM_SUCCESS)
            {
                /* Process the inquiry complete (Error Status) */
                btm_process_inq_complete (BTM_ERR_PROCESSING);

                /* btm_process_inq_complete() does not restore the following settings on periodic inquiry */
                p_inq->inqfilt_active = FALSE;
                p_inq->inq_active = BTM_INQUIRY_INACTIVE;
                p_inq->state = BTM_INQ_INACTIVE_STATE;

                return;
            }

            /* Check to see if a new filter needs to be set up */
            if (p_inq->state == BTM_INQ_CLR_FILT_STATE)
            {
                if ((status = btm_set_inq_event_filter (p_inq->inqparms.filter_cond_type, &p_inq->inqparms.filter_cond)) == BTM_CMD_STARTED)
                {
                    p_inq->state = BTM_INQ_SET_FILT_STATE;
                }
                else    /* Error setting the filter: Call the initiator's callback function to indicate a failure */
                {
                    p_inq->inqfilt_active = FALSE;

                    /* Process the inquiry complete (Error Status) */
                    btm_process_inq_complete (BTM_ERR_PROCESSING);
                }
            }
            else    /* Initiate the Inquiry or Periodic Inquiry */
            {
                p_inq->state = BTM_INQ_ACTIVE_STATE;
                p_inq->inqfilt_active = FALSE;
                btm_initiate_inquiry (p_inq);
            }
        }
    }
}

/*******************************************************************************
**
** Function         btm_process_inq_results
**
*******************************************************************************/
void btm_process_inq_results (UINT8 *p, UINT8 inq_res_mode)
{
    UINT8            num_resp, xx;
    BD_ADDR          bda;
    tINQ_DB_ENT_WII *p_i;
    tBTM_WII_INQ_RESULTS *p_cur;
    BOOLEAN          is_new = TRUE;
    tBTM_INQ_VARS   *p_inq = &btm_cb.btm_inq_vars;
    tBTM_WII_INQ_RESULTS_CB *p_inq_results_cb = (tBTM_WII_INQ_RESULTS_CB *)p_inq->p_inq_results_cb;
    UINT8            page_scan_rep_mode = 0;
    UINT8            page_scan_per_mode = 0;
    UINT8            page_scan_mode = 0;
    UINT8            rssi = 0;
    DEV_CLASS        dc;
    UINT16           clock_offset;

    /* Only process the results if the inquiry is still active */
    if (!p_inq->inq_active)
        return;

    STREAM_TO_UINT8 (num_resp, p);

    for (xx = 0; xx < num_resp; xx++)
    {
        /* Extract inquiry results */
        STREAM_TO_BDADDR   (bda, p);
        STREAM_TO_UINT8    (page_scan_rep_mode, p);
        STREAM_TO_UINT8    (page_scan_per_mode, p);

        if (inq_res_mode == BTM_INQ_RESULT_STANDARD)
        {
            STREAM_TO_UINT8(page_scan_mode, p);
        }

        STREAM_TO_DEVCLASS (dc, p);
        STREAM_TO_UINT16   (clock_offset, p);
        if (inq_res_mode != BTM_INQ_RESULT_STANDARD)
        {
            STREAM_TO_UINT8(rssi, p);
        }

        /* Check if this address has already been processed for this inquiry */
        if (btm_inq_find_bdaddr(bda))
            continue;

        /* If a filter is set, check if the device passes the filter */
        if (btm_cb.p_inq_filter_cb)
        {
            if (!(*btm_cb.p_inq_filter_cb) (bda, dc))
                continue;
        }

        /* Check if this address is already in the inquiry database */
        p_i = btm_inq_db_find (bda);

        /* If existing entry, use that, else get a new one (possibly reusing the oldest) */
        if (p_i == NULL)
        {
            p_i = btm_inq_db_new (bda);
            is_new = TRUE;
        }

        /* If an entry for the device already exists, overwrite it ONLY if it is from
           a previous inquiry. (Ignore it if it is a duplicate response from the same
           inquiry.
        */
        else if (p_i->inq_count == p_inq->inq_counter)
            is_new = FALSE;

        if (is_new == TRUE)
        {
            /* Save the info */
            p_cur = &p_i->inq_info.results;
            p_cur->page_scan_rep_mode = page_scan_rep_mode;
            p_cur->page_scan_per_mode = page_scan_per_mode;
            p_cur->page_scan_mode     = page_scan_mode;
            p_cur->dev_class[0]       = dc[0];
            p_cur->dev_class[1]       = dc[1];
            p_cur->dev_class[2]       = dc[2];
            p_cur->clock_offset       = clock_offset  | BTM_CLOCK_OFFSET_VALID;

            if (inq_res_mode != BTM_INQ_RESULT_STANDARD)
                p_cur->rssi = rssi;
            else
                p_cur->rssi = BTM_INQ_RES_IGNORE_RSSI;

            p_i->time_of_resp = GKI_get_tick_count ();

            p_i->inq_count = p_inq->inq_counter;   /* Mark entry for current inquiry */

            /* If the number of responses found and not unlimited, issue a cancel inquiry */
            p_inq->inq_cmpl_info.num_resp++;
            if (!(p_inq->inq_active & BTM_WII_PERIODIC_INQUIRY_ACTIVE) &&
                p_inq->inqparms.max_resps &&
                p_inq->inq_cmpl_info.num_resp == p_inq->inqparms.max_resps)
            {
                btsnd_hcic_inq_cancel();
            }

            /* Initialize flag to FALSE. This flag is set/used by application */
            p_i->inq_info.appl_knows_rem_name = FALSE;

            if (p_inq_results_cb)
                (p_inq_results_cb)(p_cur);

            /* If anyone is registered for change notifications, then tell him we added an entry.  */
            if (p_inq->p_inq_change_cb)
                (*(tBTM_WII_INQ_DB_CHANGE_CB *)p_inq->p_inq_change_cb) (&p_i->inq_info, TRUE);
        }
    }
}

/*******************************************************************************
**
** Function         btm_process_inq_complete
**
*******************************************************************************/
void btm_process_inq_complete (UINT8 status)
{
    tBTM_INQ_VARS *p_inq = &btm_cb.btm_inq_vars;
    tBTM_CMPL_CB  *p_inq_cb = p_inq->p_inq_cmpl_cb;

    /* Ignore any stray or late complete messages if the inquiry is not active */
    if (p_inq->inq_active)
    {
        p_inq->inq_counter++;
        p_inq->inq_cmpl_info.status = (tBTM_STATUS)((status == HCI_SUCCESS) ? BTM_SUCCESS : BTM_ERR_PROCESSING);

        /* Notify caller that the inquiry has completed; (periodic inquiries do not send completion events */
        if (!(p_inq->inq_active & BTM_WII_PERIODIC_INQUIRY_ACTIVE))
        {
            p_inq->p_inq_results_cb = (tBTM_INQ_RESULTS_CB *) NULL;
            p_inq->inq_active = BTM_INQUIRY_INACTIVE;
            p_inq->state = BTM_INQ_INACTIVE_STATE;
            p_inq->p_inq_cmpl_cb = (tBTM_CMPL_CB *) NULL;

            /* Clear the results filter */
            btm_clr_inq_result_flt();

            BTM_TRACE_DEBUG2("BTM Inq Compl Callback: status 0x%02x, num results %d",
                p_inq->inq_cmpl_info.status, p_inq->inq_cmpl_info.num_resp);

            if (p_inq_cb)
                (p_inq_cb)((tBTM_INQUIRY_CMPL *) &p_inq->inq_cmpl_info);
        }
    }
}

/*******************************************************************************
**
** Function         btm_initiate_rem_name
**
*******************************************************************************/
tBTM_STATUS  btm_initiate_rem_name (BD_ADDR remote_bda, tBTM_WII_INQ_INFO *p_cur,
                                    UINT8 origin, UINT32 timeout, tBTM_CMPL_CB *p_cb)
{
    tBTM_INQ_VARS *p_inq = &btm_cb.btm_inq_vars;
    BOOLEAN        send = TRUE;
    BOOLEAN        cmd_ok = TRUE;
    tBTM_STATUS    status = BTM_CMD_STARTED;

    /*** Make sure the device is ready ***/
    if (!BTM_IsDeviceUp())
        return (BTM_WRONG_MODE);

    if (!(p_inq->remname_active & origin))
    {
        if (origin == BTM_RMT_NAME_EXT)
        {
            if (p_inq->remname_active)
            {
                if (!memcmp (remote_bda, p_inq->remname_bda, BD_ADDR_LEN))
                    send = FALSE;
                else
                    return (BTM_BUSY);
            }
            p_inq->p_remname_cmpl_cb = p_cb;
        }
        else if (p_inq->remname_active)
            return (BTM_BUSY);

        if (send)
        {
            memcpy(p_inq->remname_bda, remote_bda, BD_ADDR_LEN);
            btu_start_timer (&p_inq->rmt_name_timer_ent, BTU_TTYPE_BTM_RMT_NAME, timeout);

            if (p_cur)
            {
                cmd_ok = btsnd_hcic_rmt_name_req (remote_bda,
                                 p_cur->results.page_scan_rep_mode,
                                 p_cur->results.page_scan_mode,
                                 (UINT16)(p_cur->results.clock_offset | BTM_CLOCK_OFFSET_VALID));
            }
            else    /* Otherwise use defaults and mark the clock offset as invalid */
            {
                cmd_ok = btsnd_hcic_rmt_name_req (remote_bda, HCI_PAGE_SCAN_REP_MODE_R1,
                                 HCI_MANDATARY_PAGE_SCAN_MODE, 0);
            }
        }

        if (cmd_ok)
            p_inq->remname_active |= origin;
        else
            status = BTM_NO_RESOURCES;
    }
    else
        status = BTM_BUSY;

    return (status);
}

/*******************************************************************************
**
** Function         btm_process_remote_name
**
*******************************************************************************/
void btm_process_remote_name (BD_ADDR bda, BD_NAME bdn, UINT16 evt_len, UINT8 hci_status)
{
    tBTM_REMOTE_DEV_NAME    rem_name;
    tBTM_INQ_VARS          *p_inq = &btm_cb.btm_inq_vars;
    tBTM_CMPL_CB           *p_cb = p_inq->p_remname_cmpl_cb;
    UINT8                  *p_n1;
    UINT16                  temp_evt_len;
    UINT8                   active = p_inq->remname_active;

    btu_stop_timer (&p_inq->rmt_name_timer_ent);
    p_inq->remname_active = FALSE;

    /* Retrieve the remote name and callback function (if there is one) */
    if (hci_status == HCI_SUCCESS)
    {
        p_n1 = (UINT8 *)rem_name.remote_bd_name;
        rem_name.length = (evt_len < BD_NAME_LEN) ? evt_len : BD_NAME_LEN;
        rem_name.status = BTM_SUCCESS;
        temp_evt_len = rem_name.length;

        while (temp_evt_len > 0)
        {
            *p_n1++ = *bdn++;
            temp_evt_len--;
        }
    }
    else
    {
        rem_name.length = 0;
        rem_name.status = BTM_BAD_VALUE_RET;
        rem_name.remote_bd_name[0] = 0;
    }

    memset(p_inq->remname_bda, 0, BD_ADDR_LEN);

    if (active & BTM_RMT_NAME_EXT)
    {
        p_inq->p_remname_cmpl_cb = NULL;
        if (p_cb)
            (p_cb)(&rem_name);
    }
}

/*******************************************************************************
**
** Function         btm_inq_rmt_name_failed
**
*******************************************************************************/
void btm_inq_rmt_name_failed (void)
{
    btm_process_remote_name (NULL, NULL, 0, HCI_ERR_UNSPECIFIED);
    btm_sec_rmt_name_request_complete (NULL, NULL, HCI_ERR_UNSPECIFIED);
}
