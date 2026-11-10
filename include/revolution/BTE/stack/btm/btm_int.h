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
 *  this file contains the main Bluetooth Manager (BTM) internal
 *  definitions.
 *
 ******************************************************************************/
#ifndef BTM_INT_H
#define BTM_INT_H

#include "bt_target.h"
#include "gki.h"
#include "sdp_api.h"
#include "hcidefs.h"

#if RFCOMM_INCLUDED == TRUE
#include "rfcdefs.h"
#endif

#include "btm_api.h"

#if (BLE_INCLUDED == TRUE)
#include "btm_ble_int.h"
#if (SMP_INCLUDED == TRUE)
#include "smp_api.h"
#endif
#endif

#if BTM_MAX_LOC_BD_NAME_LEN > 0
typedef char tBTM_LOC_BD_NAME[BTM_MAX_LOC_BD_NAME_LEN + 1];
#endif

#define  BTM_ACL_IS_CONNECTED(bda)   (btm_bda_to_acl (bda) != NULL)

/* Definitions for Server Channel Number (SCN) management
*/
#define BTM_MAX_SCN      PORT_MAX_RFC_PORTS

/* Define masks for supported and exception 2.0 ACL packet types
*/
#define BTM_ACL_SUPPORTED_PKTS_MASK      (HCI_PKT_TYPES_MASK_DM1        | \
                                          HCI_PKT_TYPES_MASK_DH1        | \
                                          HCI_PKT_TYPES_MASK_DM3        | \
                                          HCI_PKT_TYPES_MASK_DH3        | \
                                          HCI_PKT_TYPES_MASK_DM5        | \
                                          HCI_PKT_TYPES_MASK_DH5)

#define BTM_ACL_EXCEPTION_PKTS_MASK      (HCI_PKT_TYPES_MASK_NO_2_DH1   | \
                                          HCI_PKT_TYPES_MASK_NO_3_DH1   | \
                                          HCI_PKT_TYPES_MASK_NO_2_DH3   | \
                                          HCI_PKT_TYPES_MASK_NO_3_DH3   | \
                                          HCI_PKT_TYPES_MASK_NO_2_DH5   | \
                                          HCI_PKT_TYPES_MASK_NO_3_DH5)

#define BTM_EPR_AVAILABLE(p) ((HCI_ATOMIC_ENCRYPT_SUPPORTED((p)->features) && \
                               HCI_ATOMIC_ENCRYPT_SUPPORTED(btm_cb.devcb.local_features)) \
                               ? TRUE : FALSE)

#define BTM_IS_BRCM_CONTROLLER() (btm_cb.devcb.local_version.manufacturer == LMP_COMPID_BROADCOM)


/* Define the ACL Management control structure
*/
#ifndef BTM_ACL_SWKEY_STATE_IDLE
#define BTM_ACL_SWKEY_STATE_IDLE                0
#define BTM_ACL_SWKEY_STATE_MODE_CHANGE         1
#define BTM_ACL_SWKEY_STATE_ENCRYPTION_OFF      2
#define BTM_ACL_SWKEY_STATE_SWITCHING           3
#define BTM_ACL_SWKEY_STATE_ENCRYPTION_ON       4
#define BTM_ACL_SWKEY_STATE_IN_PROGRESS         5
#endif
#ifdef BTM_WII_LAYOUT
/* Wii BTE (older build): 0x11C bytes, derived from btm_acl/btm_pm asm */
typedef struct
{
    UINT16          hci_handle;         /* 0x000 */
    UINT16          pkt_types_mask;     /* 0x002 */
    UINT16          restore_pkt_types;  /* 0x004 */
    UINT16          clock_offset;       /* 0x006 */
    BD_ADDR         remote_addr;        /* 0x008 */
    DEV_CLASS       remote_dc;          /* 0x00E */
    BD_NAME         remote_name;        /* 0x011 */

    UINT16          manufacturer;       /* 0x10A */
    UINT16          lmp_subversion;     /* 0x10C */
    UINT16          link_super_tout;    /* 0x10E */
    BD_FEATURES     features;           /* 0x110 */
    UINT8           lmp_version;        /* 0x118 */

    BOOLEAN         in_use;             /* 0x119 */
    UINT8           link_role;          /* 0x11A */
    UINT8           switch_role_state;  /* 0x11B */
} tACL_CONN;
#else
typedef struct
{
    UINT16          hci_handle;
    UINT16          pkt_types_mask;
    UINT16          restore_pkt_types;  /* when coming in/out of SCO connection restore the packet types */
    UINT16          clock_offset;
    BD_ADDR         remote_addr;
    DEV_CLASS       remote_dc;
    BD_NAME         remote_name;

    UINT16          manufacturer;
    UINT16          lmp_subversion;
    UINT16          link_super_tout;
    BD_FEATURES     features;           /* Features suported by the device    */
    UINT8           lmp_version;

    BOOLEAN         in_use;
    UINT8           link_role;
    BOOLEAN         link_up_issued;     /* True if busy_level link up has been issued */

#define BTM_ACL_SWKEY_STATE_IDLE                0
#define BTM_ACL_SWKEY_STATE_MODE_CHANGE         1
#define BTM_ACL_SWKEY_STATE_ENCRYPTION_OFF      2
#define BTM_ACL_SWKEY_STATE_SWITCHING           3
#define BTM_ACL_SWKEY_STATE_ENCRYPTION_ON       4
#define BTM_ACL_SWKEY_STATE_IN_PROGRESS         5
#define BTM_ACL_SWKEY_STATE_IN_PROGRESS         5
    UINT8           switch_role_state;
    UINT8           change_key_state;

#define BTM_ACL_ENCRYPT_STATE_IDLE              0
#define BTM_ACL_ENCRYPT_STATE_ENCRYPT_OFF       1   /* encryption turning off */
#define BTM_ACL_ENCRYPT_STATE_TEMP_FUNC         2   /* temporarily off for change link key or role switch */
#define BTM_ACL_ENCRYPT_STATE_ENCRYPT_ON        3   /* encryption turning on */
    UINT8           encrypt_state;                  /* overall BTM encryption state */

#if BTM_PWR_MGR_INCLUDED == FALSE
    UINT8           mode;
#endif /* BTM_PWR_MGR_INCLUDED */
#if BLE_INCLUDED == TRUE
    UINT8           is_le_link;
#endif

} tACL_CONN;
#endif /* BTM_WII_LAYOUT */

/*****************************************************
** TIMER Definitions
******************************************************/
#define TT_DEV_RESET     1
#define TT_DEV_RLN       2
#define TT_DEV_RLNKP     4              /* Read Link Policy Settings */

/* Define the Device Management control structure
*/
#ifndef BTM_WII_LAYOUT /* Wii version is defined with tBTM_CB below */
typedef struct
{
    tBTM_DEV_STATUS_CB  *p_dev_status_cb;   /* Device status change callback        */
    tBTM_VS_EVT_CB      *p_vend_spec_cb[BTM_MAX_VSE_CALLBACKS];     /* Register for vendor specific events  */

    tBTM_CMPL_CB        *p_stored_link_key_cmpl_cb;   /* Read/Write/Delete stored link key    */

    TIMER_LIST_ENT       reset_timer;
    tBTM_CMPL_CB        *p_reset_cmpl_cb;   /* Callback function to be called       */
                                            /* when startup of the device is done   */
    TIMER_LIST_ENT       rln_timer;
    tBTM_CMPL_CB        *p_rln_cmpl_cb;     /* Callback function to be called when  */
                                            /* read local name function complete    */
    TIMER_LIST_ENT       rlinkp_timer;
    tBTM_CMPL_CB        *p_rlinkp_cmpl_cb;  /* Callback function to be called when  */
                                            /* read link policy function completes  */
    TIMER_LIST_ENT       rssi_timer;
    tBTM_CMPL_CB        *p_rssi_cmpl_cb;    /* Callback function to be called when  */
                                            /* read rssi function completes         */
    TIMER_LIST_ENT       lnk_quality_timer;
    tBTM_CMPL_CB        *p_lnk_qual_cmpl_cb;/* Callback function to be called when  */
                                            /* read link quality function completes */
    TIMER_LIST_ENT       txpwer_timer;
    tBTM_CMPL_CB        *p_txpwer_cmpl_cb;    /* Callback function to be called when  */
                                            /* read inq tx power function completes  */

    TIMER_LIST_ENT       qossu_timer;
    tBTM_CMPL_CB        *p_qossu_cmpl_cb;   /* Callback function to be called when  */
                                            /* qos setup function completes         */

    tBTM_ROLE_SWITCH_CMPL switch_role_ref_data;
    tBTM_CMPL_CB        *p_switch_role_cb;  /* Callback function to be called when  */
                                            /* requested switch role is completed   */

    tBTM_CHANGE_KEY_CMPL chg_link_key_ref_data;
    tBTM_CMPL_CB        *p_chg_link_key_cb; /* Callback function to be called when  */
                                            /* change of link key is completed      */

    TIMER_LIST_ENT       tx_power_timer;
    tBTM_CMPL_CB        *p_tx_power_cmpl_cb;   /* Callback function to be called       */

    BD_ADDR              local_addr;        /* BD_ADDR of the local device          */
    tBTM_VERSION_INFO    local_version;     /* Local Version Information            */
    BD_FEATURES          local_features;    /* Local features bit mask              */
    DEV_CLASS            dev_class;         /* Local device class                   */
#if BLE_INCLUDED == TRUE
    BD_ADDR                 read_tx_pwr_addr;   /* read TX power target address */

    tBTM_BLE_LOCAL_ID_KEYS  id_keys;            /* local BLE ID keys */
    BT_OCTET16              er;                 /* BLE encryption key */

#if BTM_BLE_CONFORMANCE_TESTING == TRUE
    BOOLEAN                 no_disc_if_pair_fail;
    BOOLEAN			        enable_test_mac_val;
    BT_OCTET8               test_mac;
    BOOLEAN			        enable_test_local_sign_cntr;
    UINT32			        test_local_sign_cntr;
#endif


#endif  /* BLE_INCLUDED */

#define BTM_DEV_STATE_WAIT_RESET_CMPLT  0
#define BTM_DEV_STATE_WAIT_AFTER_RESET  1
#define BTM_DEV_STATE_READY             2

    UINT8                state;
    tBTM_IO_CAP          loc_io_caps;       /* IO capability of the local device */
    BOOLEAN              loc_auth_req;      /* the auth_req flag  */
    BD_FEATURES          brcm_features;     /* Broadcom specific features bit mask  */
} tBTM_DEVCB;
#endif


/* Define the structures and constants used for inquiry
*/

/* Definitions of limits for inquiries */
#define BTM_PER_INQ_MIN_MAX_PERIOD      HCI_PER_INQ_MIN_MAX_PERIOD
#define BTM_PER_INQ_MAX_MAX_PERIOD      HCI_PER_INQ_MAX_MAX_PERIOD
#define BTM_PER_INQ_MIN_MIN_PERIOD      HCI_PER_INQ_MIN_MIN_PERIOD
#define BTM_PER_INQ_MAX_MIN_PERIOD      HCI_PER_INQ_MAX_MIN_PERIOD
#define BTM_MAX_INQUIRY_LENGTH          HCI_MAX_INQUIRY_LENGTH
#define BTM_MIN_INQUIRY_LEN             0x01
#define BTM_MIN_INQUIRY_LENGTH          BTM_MIN_INQUIRY_LEN

#define BTM_MIN_INQ_TX_POWER    -70
#define BTM_MAX_INQ_TX_POWER    20

#if BTM_USE_INQ_RESULTS_FILTER == TRUE
typedef struct
{
    UINT32          inq_count;          /* Used for determining if a response has already been      */
                                        /* received for the current inquiry operation. (We do not   */
                                        /* want to flood the caller with multiple responses from    */
                                        /* the same device.                                         */
    BD_ADDR         bd_addr;
} tINQ_BDADDR;
#endif

typedef struct
{
    UINT32          time_of_resp;
    UINT32          inq_count;          /* "timestamps" the entry with a particular inquiry count   */
                                        /* Used for determining if a response has already been      */
                                        /* received for the current inquiry operation. (We do not   */
                                        /* want to flood the caller with multiple responses from    */
                                        /* the same device.                                         */
    tBTM_INQ_INFO   inq_info;
    BOOLEAN         in_use;

#if (BLE_INCLUDED == TRUE)
    BOOLEAN         scan_rsp;
#endif
} tINQ_DB_ENT;


typedef struct
{
    tBTM_CMPL_CB *p_remname_cmpl_cb;

#define BTM_EXT_RMT_NAME_TIMEOUT    40


    TIMER_LIST_ENT  rmt_name_timer_ent;

    UINT16           discoverable_mode;
    UINT16           connectable_mode;
    UINT16           page_scan_window;
    UINT16           page_scan_period;
    UINT16           inq_scan_window;
    UINT16           inq_scan_period;
    UINT16           inq_scan_type;
    UINT16           page_scan_type;        /* current page scan type */

    BD_ADDR          remname_bda;           /* Name of bd addr for active remote name request */
#define BTM_RMT_NAME_INACTIVE       0
#define BTM_RMT_NAME_EXT            0x1     /* Initiated through API */
#define BTM_RMT_NAME_SEC            0x2     /* Initiated internally by security manager */
#define BTM_RMT_NAME_INQ            0x4     /* Remote name initiated internally by inquiry */
    BOOLEAN          remname_active;        /* State of a remote name request by external API */

    tBTM_CMPL_CB    *p_inq_cmpl_cb;
    tBTM_INQ_RESULTS_CB *p_inq_results_cb;
    tBTM_CMPL_CB    *p_inqfilter_cmpl_cb;   /* Called (if not NULL) after inquiry filter completed */
    tBTM_INQ_DB_CHANGE_CB *p_inq_change_cb; /* Inquiry database changed callback    */
    UINT32           inq_counter;           /* Counter incremented each time an inquiry completes */
                                            /* Used for determining whether or not duplicate devices */
                                            /* have responded to the same inquiry */
    TIMER_LIST_ENT   inq_timer_ent;
#if BTM_USE_INQ_RESULTS_FILTER == TRUE
    tINQ_BDADDR     *p_bd_db;               /* Pointer to memory that holds bdaddrs */
    UINT16           num_bd_entries;        /* Number of entries in database */
    UINT16           max_bd_entries;        /* Maximum number of entries that can be stored */
#endif
    tINQ_DB_ENT      inq_db[BTM_INQ_DB_SIZE];
    tBTM_INQ_PARMS   inqparms;              /* Contains the parameters for the current inquiry */
    tBTM_INQUIRY_CMPL inq_cmpl_info;        /* Status and number of responses from the last inquiry */

    UINT16           per_min_delay;         /* Current periodic minimum delay */
    UINT16           per_max_delay;         /* Current periodic maximum delay */
    BOOLEAN          inqfilt_active;
    UINT8            pending_filt_complete_event; /* to take care of btm_event_filter_complete corresponding to */
                                                  /* inquiry that has been cancelled*/
    UINT8            inqfilt_type;          /* Contains the inquiry filter type (BD ADDR, COD, or Clear) */

#define BTM_INQ_INACTIVE_STATE      0
#define BTM_INQ_CLR_FILT_STATE      1   /* Currently clearing the inquiry filter preceeding the inquiry request */
                                        /* (bypassed if filtering is not used)                                  */
#define BTM_INQ_SET_FILT_STATE      2   /* Sets the new filter (or turns off filtering) in this state */
#define BTM_INQ_ACTIVE_STATE        3   /* Actual inquiry or periodic inquiry is in progress */
#define BTM_INQ_REMNAME_STATE       4   /* Remote name requests are active  */

    UINT8            state;             /* Current state that the inquiry process is in */
    UINT8            inq_active;        /* Bit Mask indicating type of inquiry is active */
    BOOLEAN          no_inc_ssp;        /* TRUE, to stop inquiry on incoming SSP */
} tBTM_INQUIRY_VAR_ST;

/* The MSB of the clock offset field indicates that the offset is valid if TRUE */
#define BTM_CLOCK_OFFSET_VALID      0x8000

/* Define the structures needed by security management
*/

#define BTM_SEC_INVALID_HANDLE  0xFFFF

typedef UINT8 *BTM_BD_NAME_PTR;                        /* Pointer to Device name */

/* Security callback is called by this unit when security
**   procedures are completed.  Parameters are
**              BD Address of remote
**              Result of the operation
*/
typedef tBTM_SEC_CBACK tBTM_SEC_CALLBACK;

typedef void (tBTM_SCO_IND_CBACK) (UINT16 sco_inx) ;

/* MACROs to convert from SCO packet types mask to ESCO and back */
#define BTM_SCO_PKT_TYPE_MASK   (   HCI_PKT_TYPES_MASK_HV1      \
                                 |  HCI_PKT_TYPES_MASK_HV2      \
                                 |  HCI_PKT_TYPES_MASK_HV3)

/* Mask defining only the SCO types of an esco packet type */
#define BTM_ESCO_PKT_TYPE_MASK  (   HCI_ESCO_PKT_TYPES_MASK_HV1 \
                                 |  HCI_ESCO_PKT_TYPES_MASK_HV2 \
                                 |  HCI_ESCO_PKT_TYPES_MASK_HV3)

#define BTM_SCO_2_ESCO(scotype)  ((UINT16)(((scotype) & BTM_SCO_PKT_TYPE_MASK) >> 5))
#define BTM_ESCO_2_SCO(escotype) ((UINT16)(((escotype) & BTM_ESCO_PKT_TYPE_MASK) << 5))

/* Define masks for supported and exception 2.0 SCO packet types
*/
#define BTM_SCO_SUPPORTED_PKTS_MASK      (HCI_ESCO_PKT_TYPES_MASK_HV1       | \
                                          HCI_ESCO_PKT_TYPES_MASK_HV2       | \
                                          HCI_ESCO_PKT_TYPES_MASK_HV3       | \
                                          HCI_ESCO_PKT_TYPES_MASK_EV3       | \
                                          HCI_ESCO_PKT_TYPES_MASK_EV4       | \
                                          HCI_ESCO_PKT_TYPES_MASK_EV5)

#define BTM_SCO_EXCEPTION_PKTS_MASK      (HCI_ESCO_PKT_TYPES_MASK_NO_2_EV3  | \
                                          HCI_ESCO_PKT_TYPES_MASK_NO_3_EV3  | \
                                          HCI_ESCO_PKT_TYPES_MASK_NO_2_EV5  | \
                                          HCI_ESCO_PKT_TYPES_MASK_NO_3_EV5)


#define BTM_SCO_ROUTE_UNKNOWN       0xff

/* Define the structure that contains (e)SCO data */
typedef struct
{
    tBTM_ESCO_CBACK    *p_esco_cback;   /* Callback for eSCO events     */
    tBTM_ESCO_PARAMS    setup;
    tBTM_ESCO_DATA      data;           /* Connection complete information */
    UINT8               hci_status;
} tBTM_ESCO_INFO;

/* Define the structure used for SCO Management
*/
typedef struct
{
    tBTM_SCO_CB     *p_conn_cb;         /* Callback for when connected  */
    tBTM_SCO_CB     *p_disc_cb;         /* Callback for when disconnect */
    UINT16           state;             /* The state of the SCO link    */
    UINT16           hci_handle;        /* HCI Handle                   */
    BOOLEAN          is_orig;           /* TRUE if the originator       */
    BOOLEAN          rem_bd_known;      /* TRUE if remote BD addr known */
    tBTM_ESCO_INFO   esco;              /* Current settings             */
#if BTM_SCO_HCI_INCLUDED == TRUE
    BUFFER_Q         xmit_data_q;       /* SCO data transmitting queue  */
#endif

} tSCO_CONN;

/* SCO Management control block */
#ifdef BTM_WII_LAYOUT
/* Wii BTE (older build): 0xBC bytes at btm_cb+0x1850, derived from btm_sco asm */
typedef struct
{
    tBTM_SCO_IND_CBACK  *app_sco_ind_cb;    /* 0x00 */
    tSCO_CONN            sco_db[BTM_MAX_SCO_LINKS]; /* 0x04 (0x34 each) */
    BD_ADDR              xfer_addr;         /* 0xA0 */
    UINT16               sco_disc_reason;   /* 0xA6 */
    tBTM_ESCO_PARAMS     def_esco_parms;    /* 0xA8 */
    BOOLEAN              esco_supported;    /* 0xB8 */
    tBTM_SCO_TYPE        desired_sco_mode;  /* 0xB9 */
} tSCO_CB;
#else
typedef struct
{
    tBTM_SCO_IND_CBACK  *app_sco_ind_cb;
#if BTM_SCO_HCI_INCLUDED == TRUE
    tBTM_SCO_DATA_CB     *p_data_cb;        /* Callback for SCO data over HCI */
    UINT32               xmit_window_size; /* Total SCO window in bytes  */
#endif
    tSCO_CONN            sco_db[BTM_MAX_SCO_LINKS];
    BD_ADDR              xfer_addr;
    UINT16               sco_disc_reason;
    tBTM_ESCO_PARAMS     def_esco_parms;
    BOOLEAN              esco_supported;    /* TRUE if 1.2 cntlr AND supports eSCO links */
    tBTM_SCO_TYPE        desired_sco_mode;
    tBTM_SCO_TYPE        xfer_sco_type;
    tBTM_SCO_PCM_PARAM   sco_pcm_param;
    tBTM_SCO_CODEC_TYPE  codec_in_use;      /* None, CVSD, MSBC, etc. */
#if BTM_SCO_HCI_INCLUDED == TRUE
	tBTM_SCO_ROUTE_TYPE	 sco_path;
#endif

} tSCO_CB;
#endif /* BTM_WII_LAYOUT */


#if BTM_SCO_INCLUDED == TRUE
extern void     btm_set_sco_ind_cback( tBTM_SCO_IND_CBACK *sco_ind_cb );
extern void     btm_accept_sco_link(UINT16 sco_inx, tBTM_ESCO_PARAMS *p_setup,
                                    tBTM_SCO_CB *p_conn_cb, tBTM_SCO_CB *p_disc_cb);
extern void     btm_reject_sco_link(UINT16 sco_inx );
extern void btm_sco_chk_pend_rolechange (UINT16 hci_handle);
#else
#define btm_accept_sco_link(sco_inx, p_setup, p_conn_cb, p_disc_cb)
#define btm_reject_sco_link(sco_inx)
#define btm_set_sco_ind_cback(sco_ind_cb)
#define btm_sco_chk_pend_rolechange(hci_handle)
#endif  /* BTM_SCO_INCLUDED */

/*
** Define structure for Security Service Record.
** A record exists for each service registered with the Security Manager
*/
#ifdef BTM_WII_LAYOUT
/* Wii BTE (older build): 0x3C bytes, 24 records at btm_cb+0x1990 (btm_sec asm) */
#define BTM_WII_SEC_MAX_SERVICE_RECORDS 24
#define BTM_WII_SEC_SERVICE_NAME_LEN    21
typedef struct
{
    UINT32          mx_proto_id;        /* 0x00 */
    UINT32          orig_mx_chan_id;    /* 0x04 */
    UINT32          term_mx_chan_id;    /* 0x08 */
    UINT16          psm;                /* 0x0C */
    UINT8           security_flags;     /* 0x0E */
    UINT8           service_id;         /* 0x0F */
    UINT8           orig_service_name[BTM_WII_SEC_SERVICE_NAME_LEN + 1]; /* 0x10 */
    UINT8           term_service_name[BTM_WII_SEC_SERVICE_NAME_LEN + 1]; /* 0x26 */
} tBTM_SEC_SERV_REC;
#else
typedef struct
{
    UINT32          mx_proto_id;        /* Service runs over this multiplexer protocol */
    UINT32          orig_mx_chan_id;    /* Channel on the multiplexer protocol    */
    UINT32          term_mx_chan_id;    /* Channel on the multiplexer protocol    */
    UINT16          psm;                /* L2CAP PSM value */
    UINT16          security_flags;     /* Bitmap of required security features */
    UINT8           service_id;         /* Passed in authorization callback */
#if (L2CAP_UCD_INCLUDED == TRUE)
    UINT16          ucd_security_flags; /* Bitmap of required security features for UCD */
#endif
#if BTM_SEC_SERVICE_NAME_LEN > 0
    UINT8           orig_service_name[BTM_SEC_SERVICE_NAME_LEN + 1];
    UINT8           term_service_name[BTM_SEC_SERVICE_NAME_LEN + 1];
#endif
} tBTM_SEC_SERV_REC;
#endif /* BTM_WII_LAYOUT */

#if BLE_INCLUDED == TRUE
/* LE Security information of device in Slave Role */
typedef struct
{
    BT_OCTET16          irk;            /* peer diverified identity root */
    BT_OCTET16          ltk;            /* peer long term key */
    BT_OCTET16          csrk;           /* peer SRK peer device used to secured sign local data  */

    BT_OCTET8           rand;           /* random vector for LTK generation */
    UINT16              ediv;           /* LTK diversifier of this slave device */
    UINT16              div;            /* local DIV  to generate local LTK=d1(ER,DIV,0) and CSRK=d1(ER,DIV,1)  */
    UINT8               sec_level;      /* local pairing security level */
    UINT8               key_size;       /* key size of the LTK delivered to peer device */
    UINT8               srk_sec_level;  /* security property of peer SRK for this device */
    UINT8               local_csrk_sec_level;  /* security property of local CSRK for this device */

    UINT32              counter;        /* peer sign counter for verifying rcv signed cmd */
    UINT32              local_counter;  /* local sign counter for sending signed write cmd*/
}tBTM_SEC_BLE_KEYS;

#endif  /* BLE_INCLUDED */

typedef struct
{
    tBLE_ADDR_TYPE      ble_addr_type;  /* LE device type: public or random address */
    BD_ADDR             reconn_addr;    /* reconnect address */
    BD_ADDR             cur_rand_addr;  /* current random address */
    BD_ADDR             static_addr;    /* static address */

#if SMP_INCLUDED == TRUE
    tBTM_LE_KEY_TYPE    key_type;       /* bit mask of valid key types in record */
    tBTM_SEC_BLE_KEYS   keys;           /* LE device security info in slave rode */
#endif
} tBTM_SEC_BLE;

/*
** Define structure for Security Device Record.
** A record exists for each device authenticated with this device
*/
#ifdef BTM_WII_LAYOUT
/* Wii BTE (older build): 0x88 bytes, 16 records at btm_cb+0x1F30. Offsets derived
** from btm_dev/btm_sec/btm_pm asm; names of fields marked "inferred" are not proven. */
#define BTM_WII_SEC_MAX_DEVICE_RECORDS  16
#define BTM_WII_MAX_REM_BD_NAME_LEN     64

#define BTM_SEC_AUTHORIZED      BTM_SEC_FLAG_AUTHORIZED
#define BTM_SEC_AUTHENTICATED   BTM_SEC_FLAG_AUTHENTICATED
#define BTM_SEC_ENCRYPTED       BTM_SEC_FLAG_ENCRYPTED
#define BTM_SEC_NAME_KNOWN      0x08
#define BTM_SEC_LINK_KEY_KNOWN  BTM_SEC_FLAG_LKEY_KNOWN
#define BTM_SEC_LINK_KEY_AUTHED 0x20
#define BTM_SEC_ROLE_SWITCHED   0x40
#define BTM_SEC_IN_USE          0x80

typedef struct
{
    tBTM_SEC_SERV_REC   *p_cur_service;     /* 0x00 */
    tBTM_SEC_CALLBACK   *p_callback;        /* 0x04 */
    void                *p_ref_data;        /* 0x08 */
    UINT32               timestamp;         /* 0x0C */
    UINT32               trusted_mask[2];   /* 0x10 */
    UINT16               hci_handle;        /* 0x18 */
    UINT16               clock_offset;      /* 0x1A */
    BD_ADDR              bd_addr;           /* 0x1C */
    DEV_CLASS            dev_class;         /* 0x22 */
    LINK_KEY             link_key;          /* 0x25 */
    UINT8                sec_bd_name[BTM_WII_MAX_REM_BD_NAME_LEN + 1]; /* 0x35 */
    UINT8                sec_flags;         /* 0x76 */
    BD_FEATURES          features;          /* 0x77 */
    UINT8                sec_state;         /* 0x7F inferred */
    UINT8                is_originator;     /* 0x80 inferred */
    UINT8                security_required; /* 0x81 inferred */
    BOOLEAN              link_key_not_sent; /* 0x82 inferred */
    UINT8                link_key_type;     /* 0x83 */
    UINT8                unk_84;            /* 0x84 unknown */
    UINT8                unk_85;            /* 0x85 unknown, cleared by btm_sec_alloc_dev */
} tBTM_SEC_DEV_REC;
#else
typedef struct
{
    tBTM_SEC_SERV_REC   *p_cur_service;
    tBTM_SEC_CALLBACK   *p_callback;
    void                *p_ref_data;
    UINT32               timestamp;         /* Timestamp of the last connection   */
    UINT32               trusted_mask[BTM_SEC_SERVICE_ARRAY_SIZE];  /* Bitwise OR of trusted services     */
    UINT16               hci_handle;        /* Handle to connection when exists   */
    UINT16               clock_offset;      /* Latest known clock offset          */
    BD_ADDR              bd_addr;           /* BD_ADDR of the device              */
    DEV_CLASS            dev_class;         /* DEV_CLASS of the device            */
    LINK_KEY             link_key;          /* Device link key                    */

#define BTM_SEC_AUTHORIZED      BTM_SEC_FLAG_AUTHORIZED
#define BTM_SEC_AUTHENTICATED   BTM_SEC_FLAG_AUTHENTICATED
#define BTM_SEC_ENCRYPTED       BTM_SEC_FLAG_ENCRYPTED
#define BTM_SEC_NAME_KNOWN      0x08
#define BTM_SEC_LINK_KEY_KNOWN  BTM_SEC_FLAG_LKEY_KNOWN
#define BTM_SEC_LINK_KEY_AUTHED 0x20
#define BTM_SEC_ROLE_SWITCHED   0x40
#define BTM_SEC_IN_USE          0x80

    tBTM_BD_NAME    sec_bd_name;        /* User friendly name of the device. (may be truncated to save space in dev_rec table) */
    UINT8           sec_flags;          /* Current device security state      */
    BD_FEATURES     features;           /* Features suported by the device    */

#define BTM_SEC_STATE_IDLE              0
#define BTM_SEC_STATE_AUTHENTICATING    1
#define BTM_SEC_STATE_ENCRYPTING        2
#define BTM_SEC_STATE_GETTING_NAME      3
#define BTM_SEC_STATE_AUTHORIZING       4
#define BTM_SEC_STATE_SWITCHING_ROLE    5
#define BTM_SEC_STATE_DISCONNECTING     6
#define BTM_SEC_STATE_DELAY_FOR_ENC     7   /* delay to check for encryption to work around controller problems */

    UINT8       sec_state;              /* Operating state                    */
    BOOLEAN     is_originator;          /* TRUE if device is originating connection */
#if (L2CAP_UCD_INCLUDED == TRUE)
    BOOLEAN     is_ucd;                 /* TRUE if device is sending or receiving UCD */
                                        /* if incoming security failed, received UCD will be discarded */
#endif
    BOOLEAN     role_master;            /* TRUE if current mode is master     */
    UINT16      security_required;      /* Security required for connection   */
    BOOLEAN     link_key_not_sent;      /* link key notification has not been sent waiting for name */
    UINT8       link_key_type;          /* Type of key used in pairing   */
    BOOLEAN     link_key_changed;       /* Changed link key during current connection */

#define BTM_SM4_UNKNOWN     0x00
#define BTM_SM4_KNOWN       0x10
#define BTM_SM4_TRUE        0x11
#define BTM_SM4_REQ_PEND    0x08        /* set this bit when getting remote features */
#define BTM_SM4_UPGRADE     0x04        /* set this bit when upgrading link key */
#define BTM_SM4_RETRY       0x02        /* set this bit to retry on HCI_ERR_KEY_MISSING or HCI_ERR_LMP_ERR_TRANS_COLLISION */
#define BTM_SM4_DD_ACP      0x20        /* set this bit to indicate peer initiated dedicated bonding */
#define BTM_SM4_CONN_PEND   0x40        /* set this bit to indicate accepting acl conn; to be cleared on btm_acl_created */
    UINT8       sm4;                    /* BTM_SM4_TRUE, if the peer supports SM4 */
    tBTM_IO_CAP rmt_io_caps;            /* IO capability of the peer device */
    BOOLEAN     rmt_auth_req;           /* the auth_req flag as in the IO caps rsp evt */

#if (BLE_INCLUDED == TRUE)
    UINT8               enc_key_size;           /* current link encryption key size */
    tBTM_SEC_BLE        ble;
    tBT_DEVICE_TYPE     device_type;
    tBTM_LE_CONN_PRAMS  conn_params;
#endif

// btla-specific ++
#if BTM_DISC_DURING_RS == TRUE
#define BTM_SEC_RS_NOT_PENDING          0           /* Role Switch not in progress */
#define BTM_SEC_RS_PENDING              1           /* Role Switch in progress */
#define BTM_SEC_DISC_PENDING            2           /* Disconnect is pending */
    UINT8           rs_disc_pending;
#endif
// btla-specific --
} tBTM_SEC_DEV_REC;
#endif /* BTM_WII_LAYOUT */

#define BTM_SEC_IS_SM4(sm) ((BOOLEAN)(BTM_SM4_TRUE == ((sm)&BTM_SM4_TRUE)))
#define BTM_SEC_IS_SM4_LEGACY(sm) ((BOOLEAN)(BTM_SM4_KNOWN == ((sm)&BTM_SM4_TRUE)))
#define BTM_SEC_IS_SM4_UNKNOWN(sm) ((BOOLEAN)(BTM_SM4_UNKNOWN == ((sm)&BTM_SM4_TRUE)))


/*
** Define device configuration structure
*/
typedef struct
{
#if BTM_MAX_LOC_BD_NAME_LEN > 0
    tBTM_LOC_BD_NAME bd_name;                    /* local Bluetooth device name */
#endif
    BOOLEAN          pin_type;                   /* TRUE if PIN type is fixed */
    UINT8            pin_code_len;               /* Bonding information */
    PIN_CODE         pin_code;                   /* PIN CODE if pin type is fixed */
    BOOLEAN          connectable;                /* If TRUE page scan should be enabled */
    UINT8            def_inq_scan_mode;          /* ??? limited/general/none */
} tBTM_CFG;

#if BTM_PWR_MGR_INCLUDED == TRUE
enum
{
    BTM_PM_ST_ACTIVE  = BTM_PM_STS_ACTIVE,
    BTM_PM_ST_HOLD    = BTM_PM_STS_HOLD,
    BTM_PM_ST_SNIFF   = BTM_PM_STS_SNIFF,
    BTM_PM_ST_PARK    = BTM_PM_STS_PARK,
    BTM_PM_ST_PENDING = BTM_PM_STS_PENDING
};
typedef UINT8 tBTM_PM_STATE;

enum
{
    BTM_PM_SET_MODE_EVT,    /* Set power mode API is called. */
    BTM_PM_UPDATE_EVT,
    BTM_PM_RD_MODE_EVT     /* Read power mode API is called. */
};
typedef UINT8 tBTM_PM_EVENT;

typedef struct
{
    UINT16          event;
    UINT16          len;
    UINT8           link_ind;
} tBTM_PM_MSG_DATA;

typedef struct
{
    UINT8 hci_status;
    UINT8 mode;
    UINT16 interval;
} tBTM_PM_MD_CHG_DATA;

typedef struct
{
    UINT8          pm_id;      /* the entity that calls SetPowerMode API */
    tBTM_PM_PWR_MD *p_pmd;
} tBTM_PM_SET_MD_DATA;

typedef struct
{
    void        *p_data;
    UINT8        link_ind;
} tBTM_PM_SM_DATA;

typedef struct
{
    tBTM_PM_PWR_MD req_mode[BTM_MAX_PM_RECORDS+1]; /* the desired mode and parameters of the connection*/
    tBTM_PM_PWR_MD set_mode;  /* the mode and parameters sent down to the host controller. */
    UINT16         interval;  /* the interval from last mode change event. */
#if (BTM_SSR_INCLUDED == TRUE)
    UINT16         max_lat;   /* stored SSR maximum latency */
    UINT16         min_rmt_to;/* stored SSR minimum remote timeout */
    UINT16         min_loc_to;/* stored SSR minimum local timeout */
#endif
    tBTM_PM_STATE  state;     /* contains the current mode of the connection */
    BOOLEAN        chg_ind;   /* a request change indication */
} tBTM_PM_MCB;

#define BTM_PM_REC_NOT_USED 0
typedef struct
{
    tBTM_PM_STATUS_CBACK *cback;/* to notify the registered party of mode change event */
    UINT8                 mask; /* registered request mask. 0, if this entry is not used */
} tBTM_PM_RCB;
#endif  /* BTM_PWR_MGR_INCLUDED */

enum
{
    BTM_BLI_ACL_UP_EVT,
    BTM_BLI_ACL_DOWN_EVT,
    BTM_BLI_PAGE_EVT,
    BTM_BLI_PAGE_DONE_EVT,
    BTM_BLI_INQ_EVT,
    BTM_BLI_INQ_CANCEL_EVT,
    BTM_BLI_INQ_DONE_EVT
};
typedef UINT8 tBTM_BLI_EVENT;

/* Pairing State */
enum
{
    BTM_PAIR_STATE_IDLE,                        /* Idle                                         */
    BTM_PAIR_STATE_GET_REM_NAME,                /* Getting the remote name (to check for SM4)   */
    BTM_PAIR_STATE_WAIT_PIN_REQ,                /* Started authentication, waiting for PIN req (PIN is pre-fetched) */
    BTM_PAIR_STATE_WAIT_LOCAL_PIN,              /* Waiting for local PIN code                   */
    BTM_PAIR_STATE_WAIT_NUMERIC_CONFIRM,        /* Waiting user 'yes' to numeric confirmation   */
    BTM_PAIR_STATE_KEY_ENTRY,                   /* Key entry state (we are a keyboard)          */
    BTM_PAIR_STATE_WAIT_LOCAL_OOB_RSP,          /* Waiting for local response to peer OOB data  */
    BTM_PAIR_STATE_WAIT_LOCAL_IOCAPS,           /* Waiting for local IO capabilities and OOB data */
    BTM_PAIR_STATE_INCOMING_SSP,                /* Incoming SSP (got peer IO caps when idle)    */
    BTM_PAIR_STATE_WAIT_AUTH_COMPLETE,          /* All done, waiting authentication cpmplete    */
    BTM_PAIR_STATE_WAIT_DISCONNECT              /* Waiting to disconnect the ACL                */
};
typedef UINT8 tBTM_PAIRING_STATE;

#define BTM_PAIR_FLAGS_WE_STARTED_DD    0x01    /* We want to do dedicated bonding              */
#define BTM_PAIR_FLAGS_PEER_STARTED_DD  0x02    /* Peer initiated dedicated bonding             */
#define BTM_PAIR_FLAGS_DISC_WHEN_DONE   0x04
#define BTM_PAIR_FLAGS_PIN_REQD         0x08    /* set this bit when pin_callback is called     */
#define BTM_PAIR_FLAGS_PRE_FETCH_PIN    0x10    /* set this bit when pre-fetch pin     */
#define BTM_PAIR_FLAGS_REJECTED_CONNECT 0x20    /* set this bit when rejected incoming connection  */

typedef struct
{
    BOOLEAN             is_mux;
    BD_ADDR             bd_addr;
    UINT16              psm;
    BOOLEAN             is_orig;
    tBTM_SEC_CALLBACK   *p_callback;
    void                *p_ref_data;
    UINT32              mx_proto_id;
    UINT32              mx_chan_id;
} tBTM_SEC_QUEUE_ENTRY;

#if (L2CAP_UCD_INCLUDED == TRUE)

#define CONN_ORIENT_TERM                0x00    /* incoming connection oriented */
#define CONN_ORIENT_ORIG                0x01    /* outgoing connection oriented */
#define CONNLESS_TERM                   0x02    /* incoming connectionless      */
#define CONNLESS_ORIG                   0x03    /* outgoing connectionless      */
#define CONNECTION_TYPE_ORIG_MASK       0x01    /* mask for direction           */
#define CONNECTION_TYPE_CONNLESS_MASK   0x02    /* mask for connectionless or not */
typedef UINT8 CONNECTION_TYPE;

#else

#define CONN_ORIENT_TERM                FALSE
#define CONN_ORIENT_ORIG                TRUE
typedef BOOLEAN CONNECTION_TYPE;

#endif /* (L2CAP_UCD_INCLUDED == TRUE) */

/* Define a structure to hold all the BTM data
*/

#define BTM_STATE_BUFFER_SIZE  5                  /* size of state buffer */

#if (BTM_PCM2_INCLUDED == TRUE)
/* Define pcm2_action           */
enum
{
    BTM_PCM2_ACT_NONE,
    BTM_PCM2_ACT_SENT_ARC,
    BTM_PCM2_READ_PARAM,
    BTM_PCM2_WRITE_PARAM,
};
typedef UINT8 tBTM_PCM2_ACTION;
#endif

#ifdef BTM_WII_LAYOUT
/* Wii BTE (older build) layout of btm_cb (0x27C8 bytes). Offsets derived from the
** btm_* / l2c_* asm; names of fields marked "inferred" are not proven.
** Regions not yet derived are padding. Define BTM_WII_LAYOUT before including
** this header to use it. */
typedef struct
{
    tBTM_PM_PWR_MD req_mode[2];         /* 0x00 */
    tBTM_PM_PWR_MD set_mode;            /* 0x14 */
    UINT16         interval;            /* 0x1E */
    tBTM_PM_STATE  state;               /* 0x20 */
    BOOLEAN        chg_ind;             /* 0x21 */
} tBTM_PM_MCB_WII;

typedef struct
{
    tBTM_DEV_STATUS_CB  *p_dev_status_cb;           /* 0x568 */
    tBTM_VS_EVT_CB      *p_vend_spec_cb[1];         /* 0x56C */
    tBTM_CMPL_CB        *p_stored_link_key_cmpl_cb; /* 0x570 */
    TIMER_LIST_ENT       reset_timer;               /* 0x574 */
    tBTM_CMPL_CB        *p_reset_cmpl_cb;           /* 0x58C */
    TIMER_LIST_ENT       rln_timer;                 /* 0x590 */
    tBTM_CMPL_CB        *p_rln_cmpl_cb;             /* 0x5A8 */
    TIMER_LIST_ENT       rlinkp_timer;              /* 0x5AC */
    tBTM_CMPL_CB        *p_rlinkp_cmpl_cb;          /* 0x5C4 */
    TIMER_LIST_ENT       rssi_timer;                /* 0x5C8 */
    tBTM_CMPL_CB        *p_rssi_cmpl_cb;            /* 0x5E0 */
    TIMER_LIST_ENT       lnk_quality_timer;         /* 0x5E4 */
    tBTM_CMPL_CB        *p_lnk_qual_cmpl_cb;        /* 0x5FC */
    TIMER_LIST_ENT       qossu_timer;               /* 0x600 */
    tBTM_CMPL_CB        *p_qossu_cmpl_cb;           /* 0x618 */
    tBTM_VSC_CMPL_CB    *p_vsc_cmpl_cb;             /* 0x61C */
    tBTM_CMPL_CB        *p_hci_reset_cmpl_cb;         /* 0x620 */
    tBTM_ROLE_SWITCH_CMPL switch_role_ref_data;     /* 0x624 */
    tBTM_CMPL_CB        *p_switch_role_cb;          /* 0x62C */
    BD_ADDR              local_addr;                /* 0x630 */
    tBTM_VERSION_INFO    local_version;             /* 0x636 */
    BD_FEATURES          local_features;            /* 0x640 */
    DEV_CLASS            dev_class;                 /* 0x648 */
    UINT16               page_timeout;              /* 0x64C inferred */
    UINT8                state;                     /* 0x64E */
    UINT8                reset_tries;               /* 0x64F */
    BOOLEAN              vsc_busy;                  /* 0x650 inferred */
} tBTM_DEVCB;

#define BTM_DEV_STATE_WAIT_RESET_CMPLT  0
#define BTM_DEV_STATE_WAIT_AFTER_RESET  1
#define BTM_DEV_STATE_WAIT_HCI_BUF_SIZE 2
#define BTM_DEV_STATE_WAIT_LOCAL_VER    3
#define BTM_DEV_STATE_WAIT_LOCAL_FEAT   4
#define BTM_DEV_STATE_READY             5

/* RVL BTM keeps an SDP discovery database of its own (btm_discovery_db_*).
   Its timer is serviced by btu_task (timer type 8). */
#define BTM_DISC_DB_LEN             4000

typedef struct
{
    TIMER_LIST_ENT   disc_timer_ent;
    UINT16           num_uuid;
    tSDP_UUID        uuid;
    UINT8            unknown_30[0x48];
    tBTM_CMPL_CB    *p_disc_cmpl_cb;
    UINT8            db[BTM_DISC_DB_LEN];
    BOOLEAN          busy;
} tBTM_DISC_DB_CB;

/* Wii inquiry types (older BTE: no EIR/report_dup fields). Derived from btm_inq asm. */
typedef struct
{
    UINT16      clock_offset;           /* 0x00 */
    BD_ADDR     remote_bd_addr;         /* 0x02 */
    DEV_CLASS   dev_class;              /* 0x08 */
    UINT8       page_scan_rep_mode;     /* 0x0B */
    UINT8       page_scan_per_mode;     /* 0x0C */
    UINT8       page_scan_mode;         /* 0x0D */
    INT8        rssi;                   /* 0x0E */
} tBTM_WII_INQ_RESULTS;

typedef struct
{
    tBTM_WII_INQ_RESULTS results;       /* 0x00 */
    BOOLEAN     appl_knows_rem_name;    /* 0x10 */
} tBTM_WII_INQ_INFO;                    /* 0x12 */

typedef struct
{
    UINT8       mode;                   /* 0x00 */
    UINT8       duration;               /* 0x01 */
    UINT8       max_resps;              /* 0x02 */
    UINT8       filter_cond_type;       /* 0x03 */
    tBTM_INQ_FILT_COND filter_cond;     /* 0x04 */
} tBTM_WII_INQ_PARMS;                   /* 0x0A */

typedef struct
{
    UINT32      time_of_resp;           /* 0x00 */
    UINT32      inq_count;              /* 0x04 */
    tBTM_WII_INQ_INFO inq_info;         /* 0x08 */
    BOOLEAN     in_use;                 /* 0x1A */
} tINQ_DB_ENT_WII;                      /* 0x1C */

#define BTM_WII_INQ_DB_SIZE     12

typedef struct
{
    tBTM_CMPL_CB    *p_remname_cmpl_cb;         /* 0x167C */
    TIMER_LIST_ENT   rmt_name_timer_ent;        /* 0x1680 */
    UINT16           discoverable_mode;         /* 0x1698 */
    UINT16           connectable_mode;          /* 0x169A */
    UINT16           page_scan_window;          /* 0x169C */
    UINT16           page_scan_period;          /* 0x169E */
    UINT16           inq_scan_window;           /* 0x16A0 */
    UINT16           inq_scan_period;           /* 0x16A2 */
    UINT16           inq_scan_type;             /* 0x16A4 */
    UINT16           page_scan_type;            /* 0x16A6 */
    BD_ADDR          remname_bda;               /* 0x16A8 */
    UINT8            remname_active;            /* 0x16AE */
    tBTM_CMPL_CB    *p_inq_cmpl_cb;             /* 0x16B0 */
    tBTM_INQ_RESULTS_CB *p_inq_results_cb;      /* 0x16B4 */
    tBTM_CMPL_CB    *p_inqfilter_cmpl_cb;       /* 0x16B8 */
    tBTM_INQ_DB_CHANGE_CB *p_inq_change_cb;     /* 0x16BC */
    UINT32           inq_counter;               /* 0x16C0 */
    TIMER_LIST_ENT   inq_timer_ent;             /* 0x16C4 */
    tINQ_BDADDR     *p_bd_db;                   /* 0x16DC */
    UINT16           num_bd_entries;            /* 0x16E0 */
    UINT16           max_bd_entries;            /* 0x16E2 */
    tINQ_DB_ENT_WII  inq_db[BTM_WII_INQ_DB_SIZE]; /* 0x16E4 */
    tBTM_WII_INQ_PARMS inqparms;                /* 0x1834 */
    tBTM_INQUIRY_CMPL inq_cmpl_info;            /* 0x183E */
    UINT16           per_min_delay;             /* 0x1840 */
    UINT16           per_max_delay;             /* 0x1842 */
    BOOLEAN          inqfilt_active;            /* 0x1844 */
    UINT8            pending_filt_complete_event; /* 0x1845 */
    UINT8            inqfilt_type;              /* 0x1846 inferred */
    UINT8            state;                     /* 0x1847 */
    UINT8            inq_active;                /* 0x1848 */
} tBTM_INQUIRY_VAR_ST_WII;

typedef struct
{
    tBTM_AUTHORIZE_CALLBACK     *p_authorize_callback;      /* 0x00 */
    tBTM_PIN_CALLBACK           *p_pin_callback;            /* 0x04 */
    tBTM_LINK_KEY_CALLBACK      *p_link_key_callback;       /* 0x08 */
    tBTM_LINK_KEY_REQ_CALLBACK  *p_link_key_req_callback;   /* 0x0C */
    tBTM_AUTH_COMPLETE_CALLBACK *p_auth_complete_callback;  /* 0x10 */
    tBTM_ABORT_CALLBACK         *p_abort_callback;          /* 0x14 */
} tBTM_APPL_INFO_WII;

typedef struct
{
    char        bd_name[0x20];                      /* 0x00 */
    UINT8       pin_type;                           /* 0x20 */
    UINT8       pin_code_len;                       /* 0x21 */
    PIN_CODE    pin_code;                           /* 0x22 */
    UINT8       unk_32[2];                          /* 0x32 unknown */
} tBTM_CFG_WII;

typedef struct
{
    tBTM_CFG_WII cfg;                               /* 0x000 */
    tACL_CONN   acl_db[MAX_L2CAP_LINKS];            /* 0x034 */
    UINT8       btm_scn[0x20];                      /* 0x4A4 inferred */
    UINT16      btm_def_link_policy;                /* 0x4C4 */
    UINT16      btm_def_link_super_tout;            /* 0x4C6 */
    tBTM_ACL_DB_CHANGE_CB *p_acl_changed_cb;        /* 0x4C8 */
    tBTM_PM_MCB_WII pm_mode_db[MAX_L2CAP_LINKS];    /* 0x4CC */
    tBTM_PM_RCB pm_reg_db[2];                       /* 0x554 */
    UINT8       pm_pend_link;                       /* 0x564 */
    UINT8       pm_pend_id;                         /* 0x565 */
    tBTM_DEVCB  devcb;                              /* 0x568 */
    UINT16      btm_acl_pkt_types_supported;        /* 0x654 */
    UINT16      btm_sco_pkt_types_supported;        /* 0x656 */
    tBTM_DISC_DB_CB disc_db;                        /* 0x658 */
    tSDP_DISCOVERY_DB *p_db;                        /* 0x1678 */
    tBTM_INQUIRY_VAR_ST_WII btm_inq_vars;           /* 0x167C */
    tBTM_FILTER_CB *p_inq_filter_cb;                /* 0x184C */
    tSCO_CB     sco_cb;                             /* 0x1850 */
    tBTM_APPL_INFO_WII api;                         /* 0x190C */
    tBTM_LINK_KEY_CALLBACK *p_link_key_notif_cb[2]; /* 0x1924 inferred */
    tBTM_RMT_NAME_CALLBACK *p_rmt_name_callback[2]; /* 0x192C */
    tBTM_FILTER_CB *p_conn_filter_cb;               /* 0x1934 */
    tBTM_SEC_DEV_REC *p_collided_dev_rec;           /* 0x1938 */
    TIMER_LIST_ENT pairing_tle;                     /* 0x193C pin code timer */
    BD_ADDR     pairing_bda;                        /* 0x1954 */
    TIMER_LIST_ENT sec_collision_tle;               /* 0x195C */
    UINT32      dev_rec_count;                      /* 0x1974 */
    UINT8       security_mode;                      /* 0x1978 */
    BOOLEAN     pairing_disabled;                   /* 0x1979 */
    BOOLEAN     connect_only_paired;                /* 0x197A */
    BOOLEAN     security_mode_changed;              /* 0x197B */
    BOOLEAN     pin_type_changed;                   /* 0x197C */
    BOOLEAN     bond_created_conn;                  /* 0x197D inferred */
    UINT8       disc_reason;                        /* 0x197E */
    UINT8       pin_code_len;                       /* 0x197F */
    PIN_CODE    pin_code;                           /* 0x1980 */
    tBTM_SEC_SERV_REC sec_serv_rec[BTM_WII_SEC_MAX_SERVICE_RECORDS]; /* 0x1990 */
    tBTM_SEC_DEV_REC sec_dev_rec[BTM_WII_SEC_MAX_DEVICE_RECORDS]; /* 0x1F30 */
    tBTM_MKEY_CALLBACK *mkey_cback;                 /* 0x27B0 */
    BD_ADDR     connecting_bda;                     /* 0x27B4 */
    DEV_CLASS   connecting_dc;                      /* 0x27BA */
    UINT8       first_disabled_channel;             /* 0x27BD */
    UINT8       last_disabled_channel;              /* 0x27BE */
    UINT8       acl_disc_reason;                    /* 0x27BF */
    UINT8       trace_level;                        /* 0x27C0 */
    UINT8       unk_27c1[0x27C8 - 0x27C1];          /* 0x27C1 */
} tBTM_CB;
#else
typedef struct
{
    tBTM_CFG    cfg;                        /* Device configuration */

    /****************************************************
    **      ACL Management
    ****************************************************/
    tACL_CONN   acl_db[MAX_L2CAP_LINKS];
#if( RFCOMM_INCLUDED==TRUE)
    UINT8       btm_scn[BTM_MAX_SCN];        /* current SCNs: TRUE if SCN is in use */
#endif
    UINT16      btm_def_link_policy;
    UINT16      btm_def_link_super_tout;

#if (defined(BTM_BUSY_LEVEL_CHANGE_INCLUDED) && BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE)
    tBTM_BL_EVENT_MASK     bl_evt_mask;
    tBTM_BL_CHANGE_CB     *p_bl_changed_cb;    /* Callback for when Busy Level changed */
#else
    tBTM_ACL_DB_CHANGE_CB *p_acl_changed_cb;    /* Callback for when ACL DB changed */
#endif

    tBTM_LSTO_CBACK       *p_lsto_cback;  /* for link supervision timeout change event */

    /****************************************************
    **      Power Management
    ****************************************************/
#if BTM_PWR_MGR_INCLUDED == TRUE
    tBTM_PM_MCB pm_mode_db[MAX_L2CAP_LINKS];   /* per ACL link */
    tBTM_PM_RCB pm_reg_db[BTM_MAX_PM_RECORDS+1]; /* per application/module */
    UINT8       pm_pend_link;  /* the index of acl_db, which has a pending PM cmd */
    UINT8       pm_pend_id;    /* the id pf the module, which has a pending PM cmd */
#endif /* BTM_PWR_MGR_INCLUDED == TRUE */

    /*****************************************************
    **      Device control
    *****************************************************/
    tBTM_DEVCB  devcb;

    /*****************************************************
    **      BLE Device controllers
    *****************************************************/
#if (BLE_INCLUDED == TRUE)
    tBTM_BLE_CB             ble_ctr_cb;

    UINT16                  enc_handle;
    BT_OCTET8               enc_rand;   /* received rand value from LTK request*/
    UINT16                  ediv;       /* received ediv value from LTK request */
    UINT8                   key_size;
#endif

                                            /* Packet types supported by the local device */
    UINT16      btm_acl_pkt_types_supported;
    UINT16      btm_sco_pkt_types_supported;


    /*****************************************************
    **      Inquiry
    *****************************************************/
    tBTM_INQUIRY_VAR_ST     btm_inq_vars;
    tBTM_FILTER_CB          *p_inq_filter_cb;   /* Callback that can be set if host */
                                                /* wants to verify inquiry filters */

    /*****************************************************
    **      SCO Management
    *****************************************************/
#if BTM_SCO_INCLUDED == TRUE
    tSCO_CB             sco_cb;
#endif

    /*****************************************************
    **      Security Management
    *****************************************************/
    tBTM_APPL_INFO          api;

#define BTM_SEC_MAX_RMT_NAME_CALLBACKS  2
    tBTM_RMT_NAME_CALLBACK  *p_rmt_name_callback[BTM_SEC_MAX_RMT_NAME_CALLBACKS];

    tBTM_FILTER_CB          *p_conn_filter_cb;  /* Callback that can be set if host */
                                                /* wants to verify connectability filters*/

    tBTM_SEC_DEV_REC        *p_collided_dev_rec;
    TIMER_LIST_ENT           sec_collision_tle;
    UINT32                   collision_start_time;
    UINT32                   max_collision_delay;
    UINT32                   dev_rec_count;      /* Counter used for device record timestamp */
    UINT8                    security_mode;
    BOOLEAN                  pairing_disabled;
    BOOLEAN                  connect_only_paired;
    BOOLEAN                  security_mode_changed;  /* mode changed during bonding */
    BOOLEAN                  pin_type_changed;       /* pin type changed during bonding */
    BOOLEAN                  sec_req_pending;       /*   TRUE if a request is pending */
// btla-specific ++
#ifdef PORCHE_PAIRING_CONFLICT
    UINT8                    pin_code_len_saved;     /* for legacy devices */
#endif
// btla-specific --

    UINT8                    pin_code_len;  /* for legacy devices */
    PIN_CODE                 pin_code;      /* for legacy devices */
    tBTM_PAIRING_STATE       pairing_state; /* The current pairing state    */
    UINT8                    pairing_flags; /* The current pairing flags    */
    BD_ADDR                  pairing_bda;   /* The device currently pairing */
    TIMER_LIST_ENT           pairing_tle;   /* Timer for pairing process    */
    UINT16                   disc_handle;   /* for legacy devices */
    UINT8                    disc_reason;   /* for legacy devices */
    tBTM_SEC_SERV_REC        sec_serv_rec[BTM_SEC_MAX_SERVICE_RECORDS];
    tBTM_SEC_DEV_REC         sec_dev_rec[BTM_SEC_MAX_DEVICE_RECORDS];
    tBTM_SEC_SERV_REC       *p_out_serv;
    tBTM_MKEY_CALLBACK      *mkey_cback;

    BD_ADDR                  connecting_bda;
    DEV_CLASS                connecting_dc;

    UINT8                   first_disabled_channel;
    UINT8                   last_disabled_channel;

    UINT8                   acl_disc_reason;
    UINT8                   trace_level;
#if (defined(BTM_BUSY_LEVEL_CHANGE_INCLUDED) && BTM_BUSY_LEVEL_CHANGE_INCLUDED == TRUE)
    UINT8                   num_acl;    /* num of active ACL links */
    UINT8                   busy_level; /* the current busy level */
    BOOLEAN                 is_paging;  /* TRUE, if paging is in progess */
    BOOLEAN                 is_inquiry; /* TRUE, if inquiry is in progess */
#endif
    BUFFER_Q                page_queue;
    BOOLEAN                 paging;
    BOOLEAN                 discing;
    BUFFER_Q                sec_pending_q;  /* pending sequrity requests in tBTM_SEC_QUEUE_ENTRY format */

#if  (!defined(BT_TRACE_VERBOSE) || (BT_TRACE_VERBOSE == FALSE))
    char state_temp_buffer[BTM_STATE_BUFFER_SIZE];
#endif

#if (defined(BTM_PCM2_INCLUDED) && BTM_PCM2_INCLUDED == TRUE)
    UINT16                  sys_features;
    UINT8                   pcm2_params[BRCM_PCM2_SETUP_WRITE_SIZE];
    tBTM_PCM2_ACTION        pcm2_action;
#endif

} tBTM_CB;
#endif /* BTM_WII_LAYOUT */


#ifdef __cplusplus
extern "C"
{
#endif

#if BTM_DYNAMIC_MEMORY == FALSE
BTM_API extern tBTM_CB  btm_cb;
#else
BTM_API extern tBTM_CB *btm_cb_ptr;
#define btm_cb (*btm_cb_ptr)
#endif

/* Internal functions provided by btm_main.c
********************************************
*/
extern void         btm_init (void);

/* Internal functions provided by btm_inq.c
*******************************************
*/
extern tBTM_STATUS  btm_initiate_rem_name (BD_ADDR remote_bda,
                                           tBTM_INQ_INFO *p_cur,
                                           UINT8 origin, UINT32 timeout,
                                           tBTM_CMPL_CB *p_cb);

extern void         btm_process_remote_name (BD_ADDR bda, BD_NAME name, UINT16 evt_len,
                                             UINT8 hci_status);
extern void         btm_inq_rmt_name_failed(void);

/* Inquiry related functions */
extern void         btm_clr_inq_db (BD_ADDR p_bda);
extern void         btm_inq_db_init (void);
extern void         btm_process_inq_results (UINT8 *p, UINT8 inq_res_mode);
extern void         btm_process_inq_complete (UINT8 status, UINT8 mode);
extern void         btm_event_filter_complete (UINT8 *p);
extern void         btm_inq_stop_on_ssp(void);
extern void         btm_inq_clear_ssp(void);
extern tINQ_DB_ENT *btm_inq_db_find (BD_ADDR p_bda);
extern BOOLEAN      btm_inq_find_bdaddr (BD_ADDR p_bda);

#if (BTM_EIR_CLIENT_INCLUDED == TRUE)
extern BOOLEAN btm_lookup_eir(BD_ADDR_PTR p_rem_addr);
#endif

/* Internal functions provided by btm_acl.c
********************************************
*/
extern void         btm_acl_init (void);
extern void         btm_acl_timeout (TIMER_LIST_ENT  *p_tle);
extern void         btm_acl_created (BD_ADDR bda, DEV_CLASS dc, BD_NAME bdn,
                                     UINT16 hci_handle, UINT8 link_role, UINT8 is_le_link);
extern void         btm_acl_removed (BD_ADDR bda);
extern void         btm_acl_device_down (void);
extern void         btm_acl_update_busy_level (tBTM_BLI_EVENT event);
extern void         btm_acl_link_key_change (UINT16 handle, UINT8 status);

extern void         btm_cont_rswitch_or_chglinkkey (tACL_CONN *p,
                                                    tBTM_SEC_DEV_REC *p_dev_rec,
                                                    UINT8 hci_status);

extern UINT8        btm_handle_to_acl_index (UINT16 hci_handle);
extern void         btm_read_link_policy_complete (UINT8 *p);
extern void         btm_read_rssi_complete (UINT8 *p);
extern void         btm_read_tx_power_complete (UINT8 *p, BOOLEAN is_ble);
extern void         btm_read_link_quality_complete (UINT8 *p);
extern tBTM_STATUS  btm_set_packet_types (tACL_CONN *p, UINT16 pkt_types);
extern void         btm_process_clk_off_comp_evt (UINT16 hci_handle, UINT16 clock_offset);
extern void         btm_acl_role_changed (UINT8 hci_status, BD_ADDR bd_addr, UINT8 new_role);
extern void         btm_acl_encrypt_change (UINT16 handle, UINT8 status, UINT8 encr_enable);
BTM_API extern UINT16       btm_get_acl_disc_reason_code (void);
BTM_API extern tBTM_STATUS  btm_remove_acl (BD_ADDR bd_addr);
extern void         btm_read_remote_features_complete (UINT8 *p);
extern void         btm_read_remote_ext_features_complete (UINT8 *p);
extern void         btm_read_remote_ext_features_failed (UINT8 status);
extern void         btm_read_remote_version_complete (UINT8 *p);
// btla-specific ++
extern void         btm_acl_chk_peer_pkt_type_support (tACL_CONN *p, UINT16 *p_pkt_type);
// btla-specific --
/* Read maximum data packet that can be sent over current connection */
extern UINT16 btm_get_max_packet_size (BD_ADDR addr);
extern tACL_CONN *btm_bda_to_acl (BD_ADDR bda);
extern BOOLEAN    btm_acl_notif_conn_collision (BD_ADDR bda);

#if BTM_PWR_MGR_INCLUDED == FALSE
extern void         btm_process_mode_change (UINT8 hci_status, UINT16 hci_handle, UINT8 mode,
                                             UINT16 interval);

/* Internal functions provided by btm_pm.c
********************************************
*/
#else
extern void btm_pm_reset(void);
extern void btm_pm_sm_alloc(UINT8 ind);
extern void btm_pm_proc_cmd_status(UINT8 status);
extern void btm_pm_proc_mode_change (UINT8 hci_status, UINT16 hci_handle, UINT8 mode,
                                     UINT16 interval);
extern void btm_pm_proc_ssr_evt (UINT8 *p, UINT16 evt_len);
#if BTM_SCO_INCLUDED == TRUE
extern void btm_sco_chk_pend_unpark (UINT8 hci_status, UINT16 hci_handle);
#else
#define btm_sco_chk_pend_unpark(hci_status, hci_handle)
#endif /* BTM_SCO_INCLUDED */
#endif /* BTM_PWR_MGR_INCLUDED == FALSE */
extern void btm_qos_setup_complete (UINT8 status, UINT16 handle, FLOW_SPEC *p_flow);


/* Internal functions provided by btm_sco.c
********************************************
*/
extern void btm_sco_init (void);
extern void btm_sco_connected (UINT8 hci_status, BD_ADDR bda, UINT16 hci_handle,
                               tBTM_ESCO_DATA *p_esco_data);
extern void btm_esco_proc_conn_chg (UINT8 status, UINT16 handle, UINT8 tx_interval,
                                    UINT8 retrans_window, UINT16 rx_pkt_len,
                                    UINT16 tx_pkt_len);
extern void btm_sco_conn_req (BD_ADDR bda,  DEV_CLASS dev_class, UINT8 link_type);
extern void btm_sco_removed (UINT16 hci_handle, UINT8 reason);
extern void btm_sco_acl_removed (BD_ADDR bda);
extern void btm_route_sco_data (BT_HDR *p_msg);
extern BOOLEAN btm_is_sco_active (UINT16 handle);
extern void btm_remove_sco_links (BD_ADDR bda);
extern BOOLEAN btm_is_sco_active_by_bdaddr (BD_ADDR remote_bda);

extern tBTM_SCO_TYPE btm_read_def_esco_mode (tBTM_ESCO_PARAMS *p_parms);
extern UINT16  btm_find_scb_by_handle (UINT16 handle);
extern void btm_sco_flush_sco_data(UINT16 sco_inx);

/* Internal functions provided by btm_devctl.c
**********************************************
*/
extern void btm_dev_init (void);
extern void btm_dev_absent (void);
extern void btm_dev_timeout (TIMER_LIST_ENT *p_tle);
extern void btm_reset_complete (void);
extern void btm_read_local_version_complete (UINT8 *p, UINT16 evt_len);
extern void btm_read_hci_buf_size_complete (UINT8 *p, UINT16 evt_len);
extern void btm_read_local_features_complete (UINT8 *p, UINT16 evt_len);
extern void btm_read_local_name_complete (UINT8 *p, UINT16 evt_len);
extern void btm_read_local_addr_complete (UINT8 *p, UINT16 evt_len);
extern void btm_get_local_features (void);

#if (BLE_INCLUDED == TRUE)
extern void btm_read_ble_buf_size_complete (UINT8 *p, UINT16 evt_len);
extern void btm_read_white_list_size_complete(UINT8 *p, UINT16 evt_len);
extern void btm_ble_add_2_white_list_complete(UINT8 *p, UINT16 evt_len);
extern void btm_ble_remove_from_white_list_complete(UINT8 *p, UINT16 evt_len);
extern void btm_ble_clear_white_list_complete(UINT8 *p, UINT16 evt_len);
#endif  /* BLE_INCLUDED */

/* Vendor Specific Command complete evt handler */
#ifdef REVOLUTION
extern void btm_discovery_db_init (void);
extern void btm_discovery_db_reset (void);
extern void btm_discovery_db_timeout (void);
#endif
#ifdef REVOLUTION
extern void btm_vsc_complete (UINT8 *p, UINT16 cc_opcode, UINT16 evt_len);
#else
extern void btm_vsc_complete (UINT8 *p, UINT16 cc_opcode, UINT16 evt_len,
                              tBTM_CMPL_CB *p_vsc_cplt_cback);
#endif
extern void btm_inq_db_reset (void);
extern void btm_vendor_specific_evt (UINT8 *p, UINT8 evt_len);
extern UINT8 btm_get_hci_version (void);
extern void btm_read_stored_link_key_complete (UINT8 *p);
extern void btm_write_stored_link_key_complete (UINT8 *p);
extern void btm_delete_stored_link_key_complete (UINT8 *p);
extern void btm_return_link_keys_evt (tBTM_RETURN_LINK_KEYS_EVT *result);
extern void btm_report_device_status (tBTM_DEV_STATUS status);


/* Internal functions provided by btm_dev.c
**********************************************
*/
extern BOOLEAN btm_dev_support_switch (BD_ADDR bd_addr);
extern UINT8 btm_get_voice_coding_support (void);

extern tBTM_SEC_DEV_REC  *btm_sec_alloc_dev (BD_ADDR bd_addr);
extern void               btm_sec_free_dev (tBTM_SEC_DEV_REC *p_dev_rec);
extern tBTM_SEC_DEV_REC  *btm_find_dev (BD_ADDR bd_addr);
extern tBTM_SEC_DEV_REC  *btm_find_or_alloc_dev (BD_ADDR bd_addr);
extern tBTM_SEC_DEV_REC  *btm_find_dev_by_handle (UINT16 handle);

/* Internal functions provided by btm_sec.c
**********************************************
*/
extern BOOLEAN btm_dev_support_switch (BD_ADDR bd_addr);
extern tBTM_STATUS  btm_sec_l2cap_access_req (BD_ADDR bd_addr, UINT16 psm,
                                       UINT16 handle, CONNECTION_TYPE conn_type,
                                       tBTM_SEC_CALLBACK *p_callback, void *p_ref_data);
extern tBTM_STATUS  btm_sec_mx_access_request (BD_ADDR bd_addr, UINT16 psm, BOOLEAN is_originator,
                                        UINT32 mx_proto_id, UINT32 mx_chan_id,
                                        tBTM_SEC_CALLBACK *p_callback, void *p_ref_data);
extern void  btm_sec_conn_req (UINT8 *bda, UINT8 *dc);
extern void btm_create_conn_cancel_complete (UINT8 *p);
extern void btm_proc_lsto_evt(UINT16 handle, UINT16 timeout);
extern void btm_read_linq_tx_power_complete (UINT8 *p);

extern void  btm_sec_init (UINT8 sec_mode);
extern void  btm_sec_dev_reset (void);
extern void  btm_sec_abort_access_req (BD_ADDR bd_addr);
extern void  btm_sec_auth_complete (UINT16 handle, UINT8 status);
extern void  btm_sec_mkey_comp_event (UINT16 handle, UINT8 status, UINT8 key_flg);
extern void  btm_sec_encrypt_change (UINT16 handle, UINT8 status, UINT8 encr_enable);
extern void  btm_sec_connected (UINT8 *bda, UINT16 handle, UINT8 status, UINT8 enc_mode);
extern tBTM_STATUS btm_sec_disconnect (UINT16 handle, UINT8 reason);
extern void  btm_sec_disconnected (UINT16 handle, UINT8 reason);
extern void  btm_sec_rmt_name_request_complete (UINT8 *bd_addr, UINT8 *bd_name, UINT8 status);
extern void  btm_sec_rmt_host_support_feat_evt (UINT8 *p);
extern void  btm_io_capabilities_req (UINT8 *p);
extern void  btm_io_capabilities_rsp (UINT8 *p);
extern void  btm_proc_sp_req_evt (tBTM_SP_EVT event, UINT8 *p);
extern void  btm_keypress_notif_evt (UINT8 *p);
extern void  btm_simple_pair_complete (UINT8 *p);
extern void  btm_sec_link_key_notification (UINT8 *p_bda, UINT8 *p_link_key, UINT8 key_type);
extern void  btm_sec_link_key_request (UINT8 *p_bda);
extern void  btm_sec_pin_code_request (UINT8 *p_bda);
extern void  btm_sec_update_clock_offset (UINT16 handle, UINT16 clock_offset);
extern void  btm_sec_dev_rec_cback_event (tBTM_SEC_DEV_REC *p_dev_rec, UINT8 res);

#if BLE_INCLUDED == TRUE
extern void  btm_sec_clear_ble_keys (tBTM_SEC_DEV_REC  *p_dev_rec);
extern  BOOLEAN btm_sec_find_bonded_dev (UINT8 start_idx, UINT8 *p_found_idx, tBTM_SEC_DEV_REC *p_rec);
extern BOOLEAN btm_sec_is_a_bonded_dev (BD_ADDR bda);
#endif /* BLE_INCLUDED */

extern tINQ_DB_ENT *btm_inq_db_new (BD_ADDR p_bda);

#if BTM_OOB_INCLUDED == TRUE
extern void  btm_rem_oob_req (UINT8 *p);
extern void  btm_read_local_oob_complete (UINT8 *p);
#else
#define btm_rem_oob_req(p)
#define btm_read_local_oob_complete(p)
#endif

extern void  btm_acl_resubmit_page (void);
extern void  btm_acl_reset_paging (void);
extern void  btm_acl_paging (BT_HDR *p, BD_ADDR dest);
extern void  btm_acl_set_discing (BOOLEAN discing);
extern UINT8 btm_sec_clr_service_by_psm (UINT16 psm);

#ifdef BRCM_VS
extern void btm_brcm_feat_init(void);
extern void btm_vs_reset_complete (void);
extern void btm_brcm_arc_init (void);

#endif

#ifdef __cplusplus
}
#endif

#endif

