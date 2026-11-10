/******************************************************************************
 *
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

/******************************************************************************
 *
 *  This file contains the definition of the btm control block when
 *  BTM_DYNAMIC_MEMORY is used.
 *
 ******************************************************************************/

#include "bt_types.h"
#include "bt_target.h"
#include <string.h>
#include "btm_int.h"

/* Global BTM control block structure
*/
#if BTM_DYNAMIC_MEMORY == FALSE
extern tBTM_CB btm_cb;
#endif

/*******************************************************************************
**
** Function         btm_init
**
** Description      This function is called at BTM startup to allocate the
**                  control block (if using dynamic memory), and initializes the
**                  tracing level.  It then initializes the various components of
**                  btm.
**
** Returns          void
**
*******************************************************************************/
void btm_init(void)
{
    memset(&btm_cb, 0, 0x27c4);
    /* Wii control block trace level; the imported stack has a newer layout. */
    *((UINT8*)&btm_cb + 0x27c0) = BT_TRACE_LEVEL_NONE;
    btm_inq_db_init();
    btm_acl_init();
    btm_sec_init(BTM_SEC_MODE_SERVICE);
    btm_sco_init();
    btm_dev_init();
}


