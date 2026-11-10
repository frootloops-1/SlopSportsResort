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
 *  This file contains functions for the Bluetooth Device Manager
 *
 ******************************************************************************/

/* Wii (older BTE) structure layouts */
#define BTM_WII_LAYOUT
#define L2C_WII_LAYOUT

#define BTM_SecAddDevice BTM_SecAddDevice_proto_unused
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
#include "l2c_api.h"
#undef BTM_SecAddDevice

/* Wii BTE (older build): bodies rewritten from the RSPE01_01 asm. */

tBTM_SEC_DEV_REC *btm_find_oldest_dev (void);

/*******************************************************************************
**
** Function         BTM_SecAddDevice
**
** Description      Add/modify device.  This function will be normally called
**                  during host startup to restore all required information
**                  stored in the NVRAM.
**
** Returns          TRUE if added OK, else FALSE
**
*******************************************************************************/
BOOLEAN BTM_SecAddDevice (BD_ADDR bd_addr, DEV_CLASS dev_class, BD_NAME bd_name,
                          BD_FEATURES features, UINT32 trusted_mask[],
                          LINK_KEY link_key)
{
    tBTM_SEC_DEV_REC  *p_dev_rec;

    p_dev_rec = btm_find_dev (bd_addr);
    if (!p_dev_rec)
    {
        /* There is no device record, allocate one.
         * If we can not find an empty spot for this one, let it fail. */
        if ((p_dev_rec = btm_sec_alloc_dev (bd_addr)) == NULL)
            return(FALSE);
    }
    else
    {
        p_dev_rec->timestamp = btm_cb.dev_rec_count++;
    }

    if (dev_class)
        memcpy (p_dev_rec->dev_class, dev_class, DEV_CLASS_LEN);

    memset(p_dev_rec->sec_bd_name, 0, sizeof(p_dev_rec->sec_bd_name));

    if (bd_name && bd_name[0])
    {
        p_dev_rec->sec_flags |= BTM_SEC_NAME_KNOWN;
        strncpy ((char *)p_dev_rec->sec_bd_name, (char *)bd_name, BTM_WII_MAX_REM_BD_NAME_LEN);
    }

    if (features)
        memcpy (p_dev_rec->features, features, sizeof (BD_FEATURES));
    else
        memset (p_dev_rec->features, 0, sizeof (BD_FEATURES));

    /* Wii: two trusted-service words */
    p_dev_rec->trusted_mask[0] = trusted_mask[0];
    p_dev_rec->trusted_mask[1] = trusted_mask[1];

    if (link_key)
    {
        p_dev_rec->sec_flags |= BTM_SEC_LINK_KEY_KNOWN;
        memcpy (p_dev_rec->link_key, link_key, LINK_KEY_LEN);
    }

    return(TRUE);
}

/*******************************************************************************
**
** Function         BTM_SecDeleteDevice
**
** Description      Free resources associated with the device.
**
** Returns          TRUE if removed OK, FALSE if not found
**
*******************************************************************************/
BOOLEAN BTM_SecDeleteDevice(BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    if ((p_dev_rec = btm_find_dev(bd_addr)) == NULL)
        return FALSE;
    p_dev_rec->sec_flags = 0;
    BTM_DeleteStoredLinkKey(bd_addr, NULL);
    return TRUE;
}

/*******************************************************************************
**
** Function         BTM_SecReadDevName
**
** Description      Looks for the device name in the security database for the
**                  specified BD address.
**
** Returns          Pointer to the name or NULL
**
*******************************************************************************/
char *BTM_SecReadDevName(BD_ADDR bd_addr)
{
    char *p_name = NULL;
    tBTM_SEC_DEV_REC *p_srec;
    if ((p_srec = btm_find_dev(bd_addr)) != NULL)
        p_name = (char *)p_srec->sec_bd_name;
    return p_name;
}

/*******************************************************************************
**
** Function         btm_sec_alloc_dev
**
** Description      Allocate a record in the device database
**
** Returns          Pointer to the record
**
*******************************************************************************/
tBTM_SEC_DEV_REC *btm_sec_alloc_dev (BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC *p_dev_rec = NULL;
    tBTM_INQ_INFO    *p_inq_info;
    int               i;
    for (i = 0; i < BTM_WII_SEC_MAX_DEVICE_RECORDS; i++)
    {
        if (!(btm_cb.sec_dev_rec[i].sec_flags & BTM_SEC_IN_USE))
        {
            p_dev_rec = &btm_cb.sec_dev_rec[i];
            break;
        }
    }

    if (!p_dev_rec)
        p_dev_rec = btm_find_oldest_dev();

    memset (p_dev_rec, 0, sizeof (tBTM_SEC_DEV_REC));

    p_dev_rec->sec_flags = BTM_SEC_IN_USE;
    p_dev_rec->unk_85 = 0;

    /* Check with the BT manager if details about remote device are known */
    if ((p_inq_info = BTM_InqDbRead(bd_addr)) != NULL)
        memcpy (p_dev_rec->dev_class, p_inq_info->results.dev_class, DEV_CLASS_LEN);
    else
        memcpy (p_dev_rec->dev_class, btm_cb.connecting_dc, DEV_CLASS_LEN);

    memcpy (p_dev_rec->bd_addr, bd_addr, BD_ADDR_LEN);

    p_dev_rec->hci_handle = BTM_GetHCIConnHandle (bd_addr);
    p_dev_rec->timestamp = btm_cb.dev_rec_count++;

    return(p_dev_rec);
}

/*******************************************************************************
**
** Function         btm_find_dev_by_handle
**
** Description      Look for the record in the device database for the record
**                  with specified handle
**
** Returns          Pointer to the record or NULL
**
*******************************************************************************/
tBTM_SEC_DEV_REC *btm_find_dev_by_handle(UINT16 handle)
{
    tBTM_SEC_DEV_REC *p_dev_rec = &btm_cb.sec_dev_rec[0];
    int i;
    for (i = 0; i < BTM_WII_SEC_MAX_DEVICE_RECORDS; i++, p_dev_rec++)
    {
        if ((p_dev_rec->sec_flags & BTM_SEC_IN_USE) &&
            p_dev_rec->hci_handle == handle)
            return p_dev_rec;
    }
    return NULL;
}

/*******************************************************************************
**
** Function         btm_find_dev
**
** Description      Look for the record in the device database for the record
**                  with specified BD address
**
** Returns          Pointer to the record or NULL
**
*******************************************************************************/
tBTM_SEC_DEV_REC *btm_find_dev(BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC *p_dev_rec = &btm_cb.sec_dev_rec[0];
    int i;
    for (i = 0; i < BTM_WII_SEC_MAX_DEVICE_RECORDS; i++, p_dev_rec++)
    {
        if ((p_dev_rec->sec_flags & BTM_SEC_IN_USE) &&
            !memcmp(p_dev_rec->bd_addr, bd_addr, BD_ADDR_LEN))
            return p_dev_rec;
    }
    return NULL;
}

/*******************************************************************************
**
** Function         btm_find_oldest_dev
**
** Description      Locates the oldest device in use. It first looks for
**                  the oldest non-paired device.  If all devices are paired it
**                  deletes the oldest paired device.
**
** Returns          Pointer to the record or NULL
**
*******************************************************************************/
tBTM_SEC_DEV_REC *btm_find_oldest_dev (void)
{
    tBTM_SEC_DEV_REC *p_dev_rec = &btm_cb.sec_dev_rec[0];
    tBTM_SEC_DEV_REC *p_oldest = p_dev_rec;
    UINT32       ot = 0xFFFFFFFF;
    int i;

    /* First look for the non-paired devices for the oldest entry */
    for (i = 0; i < BTM_WII_SEC_MAX_DEVICE_RECORDS; i++, p_dev_rec++)
    {
        if (((p_dev_rec->sec_flags & BTM_SEC_IN_USE) == 0)
            || ((p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_KNOWN) != 0))
            continue; /* Device is paired so skip it */

        if (p_dev_rec->timestamp < ot)
        {
            p_oldest = p_dev_rec;
            ot       = p_dev_rec->timestamp;
        }
    }

    if (ot != 0xFFFFFFFF)
        return(p_oldest);

    /* All devices are paired; find the oldest */
    p_dev_rec = &btm_cb.sec_dev_rec[0];
    for (i = 0; i < BTM_WII_SEC_MAX_DEVICE_RECORDS; i++, p_dev_rec++)
    {
        if ((p_dev_rec->sec_flags & BTM_SEC_IN_USE) == 0)
            continue;

        if (p_dev_rec->timestamp < ot)
        {
            p_oldest = p_dev_rec;
            ot       = p_dev_rec->timestamp;
        }
    }
    return(p_oldest);
}
