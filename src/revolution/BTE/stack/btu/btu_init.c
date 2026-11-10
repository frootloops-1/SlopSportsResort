/******************************************************************************
 *
 *  Copyright (C) 2000-2012 Broadcom Corporation
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
 *  This module contains the routines that load and shutdown the core stack
 *  components.
 *
 ******************************************************************************/

#include "bt_target.h"
#include <string.h>
#include "dyn_mem.h"

#include "btu.h"
#include "btm_int.h"
#include "sdpint.h"
#include "l2c_int.h"

#if (BLE_INCLUDED == TRUE)
#include "gatt_api.h"
#include "gatt_int.h"
#if SMP_INCLUDED == TRUE
#include "smp_int.h"
#endif
#endif

extern void PLATFORM_DisableHciTransport(UINT8 bDisable);
/*****************************************************************************
**                          V A R I A B L E S                                *
******************************************************************************/
#if 0 /* defined in l2c_api.c split (.sdata2 0x804C13D0) in the Wii binary */
const BD_ADDR   BT_BD_ANY = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
#endif

/*****************************************************************************
**                          F U N C T I O N S                                *
******************************************************************************/
/*****************************************************************************
**
** Function         btu_init_core
**
** Description      Initialize control block memory for each core component.
**
**
** Returns          void
**
******************************************************************************/
BT_API void btu_init_core(void)
{
/* Initialize the optional stack components */

/****************************
** RFCOMM and its profiles **
*****************************/
#if (defined(RFCOMM_INCLUDED) && RFCOMM_INCLUDED == TRUE)
    btm_init();

#if (defined(SPP_INCLUDED) && SPP_INCLUDED == TRUE)
    SPP_Init();
#endif  /* SPP */

#if (defined(DUN_INCLUDED) && DUN_INCLUDED == TRUE)
    DUN_Init();
#endif  /* DUN */

#if (defined(HSP2_INCLUDED) && HSP2_INCLUDED == TRUE)
    HSP2_Init();
#endif  /* HSP2 */

#if (defined(HFP_INCLUDED) && HFP_INCLUDED == TRUE)
    HFP_Init();
#endif  /* HFP */

/**************************
** OBEX and its profiles **
***************************/
#if (defined(OBX_INCLUDED) && OBX_INCLUDED == TRUE)
    OBX_Init();
#if (defined(BIP_INCLUDED) && BIP_INCLUDED == TRUE)
    BIP_Init();
#if (defined(BTU_BTA_INCLUDED) && BTU_BTA_INCLUDED == TRUE)
#if (defined(BTA_BI_INCLUDED) && BTA_BI_INCLUDED == TRUE)
    BTA_BicInit();
#endif  /* BTA BI */
#endif
#endif  /* BIP */

#if (defined(GOEP_INCLUDED) && GOEP_INCLUDED == TRUE)
    GOEP_Init();
#endif /* GOEP */


#if (defined(FTP_INCLUDED) && FTP_INCLUDED == TRUE)
    FTP_Init();
#endif
#if (defined(OPP_INCLUDED) && OPP_INCLUDED == TRUE)
    OPP_Init();
#endif

#if (defined(BPP_INCLUDED) && BPP_INCLUDED == TRUE)
    BPP_Init();
#endif  /* BPP */
#endif  /* OBX */


#endif  /* RFCOMM Included */

/*************************
** TCS and its profiles **
**************************/
#if (defined(TCS_INCLUDED) && TCS_INCLUDED == TRUE)
    TCS_Init();

#if (defined(CTP_INCLUDED) && CTP_INCLUDED == TRUE)
    CTP_Init();
#endif /* CTP_INCLUDED */

#if (defined(ICP_INCLUDED) && ICP_INCLUDED == TRUE)
    ICP_Init();
#endif /* ICP_INCLUDED */

#endif /* TCS_INCLUDED */


/**************************
** BNEP and its profiles **
***************************/
#if (defined(BNEP_INCLUDED) && BNEP_INCLUDED == TRUE)
    BNEP_Init();

#if (defined(PAN_INCLUDED) && PAN_INCLUDED == TRUE)
    PAN_Init();
#endif  /* PAN */
#endif  /* BNEP Included */


/**************************
** AVDT and its profiles **
***************************/
#if (defined(A2D_INCLUDED) && A2D_INCLUDED == TRUE)
    A2D_Init();
#endif  /* AADP */


#if (defined(AVRC_INCLUDED) && AVRC_INCLUDED == TRUE)
    AVRC_Init();
#endif


/***********
** Others **
************/
#if (defined(GAP_INCLUDED) && GAP_INCLUDED == TRUE)
    l2c_init();
#endif  /* GAP Included */

#if (defined(HCRP_INCLUDED) && HCRP_INCLUDED == TRUE)
#if (defined(HCRP_CLIENT_INCLUDED) && HCRP_CLIENT_INCLUDED == TRUE)
    HCRP_Init();
#endif
#if (defined(HCRP_SERVER_INCLUDED) && HCRP_SERVER_INCLUDED == TRUE)
    HCRPM_Init();
#endif
#endif  /* HCRP Included */

#if (defined(SAP_SERVER_INCLUDED) && SAP_SERVER_INCLUDED == TRUE)
    SAP_Init();
#endif  /* SAP_SERVER_INCLUDED */

#if (defined(HID_DEV_INCLUDED) && HID_DEV_INCLUDED == TRUE)
    sdp_init();
#endif
#if (defined(HID_HOST_INCLUDED) && HID_HOST_INCLUDED == TRUE)
    btm_discovery_db_init();
#endif

#if (defined(MCA_INCLUDED) && MCA_INCLUDED == TRUE)
    MCA_Init();
#endif  /* SAP_SERVER_INCLUDED */

/****************
** BTA Modules **
*****************/
// btla-specific ++
#if (BTA_INCLUDED == TRUE && BTA_DYNAMIC_MEMORY == TRUE)
    memset((void*)bta_sys_cb_ptr, 0, sizeof(tBTA_SYS_CB));
    memset((void*)bta_dm_cb_ptr, 0, sizeof(tBTA_DM_CB));
    memset((void*)bta_dm_search_cb_ptr, 0, sizeof(tBTA_DM_SEARCH_CB));
    memset((void*)bta_dm_di_cb_ptr, 0, sizeof(tBTA_DM_DI_CB));
    memset((void*)bta_prm_cb_ptr, 0, sizeof(tBTA_PRM_CB));

#if BTA_AC_INCLUDED == TRUE
    memset((void*)bta_acc_cb_ptr, 0, sizeof(tBTA_ACC_CB));
    memset((void*)bta_acs_cb_ptr, 0, sizeof(tBTA_ACS_CB));
#endif
#if BTA_AG_INCLUDED == TRUE
    memset((void*)bta_ag_cb_ptr, 0, sizeof(tBTA_AG_CB));
#endif
#if BTA_HS_INCLUDED == TRUE
    memset((void*)bta_hs_cb_ptr, 0, sizeof(tBTA_HS_CB));
#endif
#if BTA_DG_INCLUDED == TRUE
    memset((void*)bta_dg_cb_ptr, 0, sizeof(tBTA_DG_CB));
#endif
#if BTA_FT_INCLUDED==TRUE
    memset((void*)bta_ftc_cb_ptr, 0, sizeof(tBTA_FTC_CB));
    memset((void*)bta_fts_cb_ptr, 0, sizeof(tBTA_FTS_CB));
#endif
#if BTA_PBC_INCLUDED==TRUE
    memset((void*)bta_pbc_cb_ptr, 0, sizeof(tBTA_PBC_CB));
#endif
#if BTA_PBS_INCLUDED==TRUE
    memset((void*)bta_pbs_cb_ptr, 0, sizeof(tBTA_PBS_CB));
#endif
#if BTA_OP_INCLUDED==TRUE
    memset((void*)bta_opc_cb_ptr, 0, sizeof(tBTA_OPC_CB));
    memset((void*)bta_ops_cb_ptr, 0, sizeof(tBTA_OPS_CB));
#endif
#if BTA_SS_INCLUDED==TRUE
    memset((void*)bta_ss_cb_ptr, 0, sizeof(tBTA_SS_CB));
#endif
#if BTA_CT_INCLUDED==TRUE
    memset((void*)bta_ct_cb_ptr, 0, sizeof(tBTA_CT_CB));
#endif
#if BTA_CG_INCLUDED==TRUE
    memset((void*)bta_cg_cb_ptr, 0, sizeof(tBTA_CG_CB));
#endif
#if BTA_BI_INCLUDED==TRUE
    memset((void *)bta_bic_cb_ptr, 0, sizeof(tBTA_BIC_CB));
    memset((void *)bta_bis_cb_ptr, 0, sizeof(tBTA_BIS_CB));
#endif
#if BTA_AR_INCLUDED==TRUE
    memset((void *)bta_ar_cb_ptr, 0, sizeof(tBTA_AR_CB));
#endif
#if BTA_AV_INCLUDED==TRUE
    memset((void *)bta_av_cb_ptr, 0, sizeof(tBTA_AV_CB));
#endif
#if BTA_PR_INCLUDED==TRUE
    memset((void *)bta_pr_cb_ptr, 0, sizeof(tBTA_PR_CB));
#endif
#if BTA_SC_INCLUDED==TRUE
    memset((void *)bta_sc_cb_ptr, 0, sizeof(tBTA_SC_CB));
#endif
#if BTA_HD_INCLUDED==TRUE
    memset((void *)bta_hd_cb_ptr, 0, sizeof(tBTA_HD_CB));
#endif
#if BTA_HH_INCLUDED==TRUE
    memset((void *)bta_hh_cb_ptr, 0, sizeof(tBTA_HH_CB));
#endif
#if BTA_FM_INCLUDED==TRUE
    memset((void *)bta_fm_cb_ptr, 0, sizeof(tBTA_FM_CB));
#endif
#if BTA_FMTX_INCLUDED==TRUE
    memset((void *)bta_fmtx_cb_ptr, 0, sizeof(tBTA_FMTX_CB));
#endif
#if 0
#if BTA_JV_INCLUDED==TRUE
    memset((void *)bta_jv_cb_ptr, 0, sizeof(tBTA_JV_CB));
#endif
#endif
#if BTA_HL_INCLUDED==TRUE
    memset((void *)bta_hl_cb_ptr, 0, sizeof(tBTA_HL_CB));
#endif
#if BTA_GATT_INCLUDED==TRUE
    memset((void *)bta_gattc_cb_ptr, 0, sizeof(tBTA_GATTC_CB));
    memset((void *)bta_gatts_cb_ptr, 0, sizeof(tBTA_GATTS_CB));
#endif
#if BTA_PAN_INCLUDED==TRUE
    memset((void *)bta_pan_cb_ptr, 0, sizeof(tBTA_PAN_CB));
#endif

#endif /* BTA_INCLUDED == TRUE */
// btla-specific --
}


/*****************************************************************************
**
** Function         BTE_Init
**
** Description      Initializes the BTU control block.
**
**                  NOTE: Must be called before creating any tasks
**                      (RPC, BTU, HCIT, APPL, etc.)
**
** Returns          void
**
******************************************************************************/
void BTE_Init(void)
{
    memset(&btu_cb, 0, 0x84);
    btu_cb.hcit_acl_pkt_size = BTU_DEFAULT_DATA_SIZE + HCI_DATA_PREAMBLE_SIZE;
    btu_cb.controller_cmd_window = 1;
}


/*****************************************************************************
**
** Function         BTU_AclPktSize
**
** Description      export the ACL packet size.
**
** Returns          UINT16
**
******************************************************************************/
UINT16 BTU_AclPktSize(void)
{
    return btu_cb.hcit_acl_pkt_size;
}
/*****************************************************************************
**
** Function         BTU_BleAclPktSize
**
** Description      export the BLE ACL packet size.
**
** Returns          UINT16
**
******************************************************************************/
UINT16 BTU_BleAclPktSize(void)
{
#if BLE_INCLUDED == TRUE
    return btu_cb.hcit_ble_acl_pkt_size;
#else
    return 0;
#endif
}

/*******************************************************************************
**
** Function         btu_uipc_rx_cback
**
** Description
**
**
** Returns          void
**
*******************************************************************************/
#ifndef REVOLUTION
void btu_uipc_rx_cback(BT_HDR *p_msg)
{
    BT_TRACE_3 (TRACE_LAYER_BTM, TRACE_TYPE_DEBUG, "btu_uipc_rx_cback event 0x%x, len %d, offset %d",
		p_msg->event, p_msg->len, p_msg->offset);
    GKI_send_msg(BTU_TASK, BTU_HCI_RCV_MBOX, p_msg);

}
#endif

