/******************************************************************************
 *
 *  Copyright (C) 2016 The Android Open Source Project
 *  Copyright (C) 2002-2012 Broadcom Corporation
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
#ifndef HIDD_API_H
#define HIDD_API_H

/* The Revolution HID device API differs from the later Android one. The types
 * below are reconstructed from how hidd_api.c, hidd_conn.c and hidd_pm.c use
 * them (field names and event numbers from the code; sizes checked against
 * the offsets noted in hidd_int.h).
 */

#include "hiddefs.h"
#include "sdp_api.h"
#include "bt_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *  Type Definitions
 ****************************************************************************/

/* Power management parameters (same layout as tBTM_PM_PWR_MD, 0x0a bytes) */
typedef struct hid_dev_pwr_md
{
    UINT16 max;
    UINT16 min;
    UINT16 attempt;
    UINT16 timeout;
    UINT8  mode;
} tHID_DEV_PWR_MD;

/* Current power mode, 0x04 bytes */
typedef struct hid_dev_curr_pm_setting
{
    UINT8  mode;
    UINT16 interval;
} tHID_DEV_CURR_PM_SETTING;

/* Quality of service for the control channel, interrupt channel and ACL link,
 * 0x48 bytes
 */
typedef struct hid_dev_qos_info
{
    FLOW_SPEC ctrl_ch;
    FLOW_SPEC int_ch;
    FLOW_SPEC hci;
} tQOS_INFO;

/* Data for a GET_REPORT request from the host */
typedef struct hid_dev_rep_data
{
    UINT8 rep_type;
    UINT8 rep_id;
} tHID_DEV_REP_DATA;

/* Third argument of the application callback; which member is valid depends
 * on the event (inferred: callers cast the address of a local to a pointer to
 * this type)
 */
typedef union hid_dev_reg_info_cback_data
{
    UINT8             u8;
    UINT16            u16;
    UINT32            u32;
    BT_HDR            *p_buf;
    tHID_DEV_REP_DATA get_rep;
} tHID_DEV_REG_INFO_CBACK_DATA;

typedef void (tHID_DEV_REG_INFO_CBACK)(UINT8 event, UINT8 param,
                                       tHID_DEV_REG_INFO_CBACK_DATA *p_data);

typedef struct hid_dev_reg_info
{
    BD_ADDR                 host_addr;
    tQOS_INFO               *qos_info;
    tHID_DEV_REG_INFO_CBACK *app_cback;
} tHID_DEV_REG_INFO;

/*****************************************************************************
 *  External Function Declarations
 ****************************************************************************/

extern void HID_DevInit(void);

extern UINT32 HID_DevSetSDPRecord(tHID_DEV_SDP_INFO *p_sdp_info);

extern tHID_STATUS HID_DevRegister(tHID_DEV_REG_INFO *p_reg_info);

extern tHID_STATUS HID_DevDeregister(void);

extern tHID_STATUS HID_DevConnect(void);

extern tHID_STATUS HID_DevDisconnect(void);

extern tHID_STATUS HID_DevHandShake(UINT8 res_code);

extern tHID_STATUS HID_DevVirtualUnplug(void);

extern tHID_STATUS HID_DevSendData(UINT8 control_ch, UINT8 rep_type,
                                   BT_HDR *data_buf);

extern tHID_STATUS HID_DevSetSecurityLevel(char *serv_name, UINT8 sec_lvl);

extern tHID_STATUS HID_DevSetPowerMgmtParams(UINT8 conn_substate,
                                             tHID_DEV_PWR_MD pm_params);

#ifdef __cplusplus
}
#endif

#endif /* HIDD_API_H */
