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
 *  This file contains L2CAP utility functions
 *
 ******************************************************************************/

/* Wii (older BTE) structure layouts in l2c_int.h */
#define BTM_WII_LAYOUT
#define L2C_WII_LAYOUT

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "gki.h"
#include "bt_types.h"
#include "hcimsgs.h"
#include "l2cdefs.h"
#include "l2c_int.h"
#include "hcidefs.h"
#include "btu.h"
#include "btm_api.h"
#include "btm_int.h"
#include "hcidefs.h"

/* L2CAP control block (.bss of this TU) */
tL2C_CB l2cb;

/*******************************************************************************
**
** Function         l2cu_allocate_lcb
**
** Description      Look for an unused LCB
**
** Returns          LCB address or NULL if none found
**
*******************************************************************************/
tL2C_LCB *l2cu_allocate_lcb (BD_ADDR p_bd_addr)
{
    int         xx;
    tL2C_LCB    *p_lcb = &l2cb.lcb_pool[0];

    for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p_lcb++)
    {
        if (!p_lcb->in_use)
        {
            memset (p_lcb, 0, sizeof (tL2C_LCB));

            p_lcb->in_use = TRUE;
            memcpy (p_lcb->remote_bd_addr, p_bd_addr, BD_ADDR_LEN);

            p_lcb->link_state      = LST_DISCONNECTED;
            p_lcb->handle          = HCI_INVALID_HANDLE;
            p_lcb->p_hcit_rcv_acl  = NULL;
            p_lcb->link_flush_tout = 0xFFFF;
            p_lcb->timer_entry.param = (TIMER_PARAM_TYPE)p_lcb;
            p_lcb->link_xmit_quota = 0;
            p_lcb->idle_timeout    = l2cb.idle_timeout;
            p_lcb->id              = 0;

            l2cb.num_links_active++;

            l2c_link_adjust_allocation();
            return (p_lcb);
        }
    }

    /* If here, no free LCB found */
    return (NULL);
}

/*******************************************************************************
**
** Function         l2cu_release_lcb
**
** Description      Release an LCB. All timers will be stopped, channels
**                  dropped, buffers returned etc.
**
** Returns          void
**
*******************************************************************************/
void l2cu_release_lcb (tL2C_LCB *p_lcb)
{
    tL2C_CCB    *p_ccb;

    p_lcb->in_use = FALSE;

    /* Stop timers */
    btu_stop_timer (&p_lcb->timer_entry);

    /* Release any unfinished L2CAP packet on this link */
    if (p_lcb->p_hcit_rcv_acl)
    {
        GKI_freebuf(p_lcb->p_hcit_rcv_acl);
        p_lcb->p_hcit_rcv_acl = NULL;
    }

    /* Release all SCO links */
    btm_remove_sco_links(p_lcb->remote_bd_addr);

    /* Ensure no CCBs left on this LCB */
    for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_lcb->ccb_queue.p_first_ccb)
    {
        l2cu_release_ccb (p_ccb);
    }

    /* Tell BTM Acl management the link was removed */
    if ((p_lcb->link_state == LST_CONNECTED) || (p_lcb->link_state == LST_DISCONNECTING))
        btm_acl_removed (p_lcb->remote_bd_addr);

    /* Release any held buffers */
    while (p_lcb->link_xmit_data_q.p_first)
        GKI_freebuf (GKI_dequeue (&p_lcb->link_xmit_data_q));

    /* Re-adjust flow control windows make sure it does not go negative */
    if (l2cb.num_links_active >= 1)
        l2cb.num_links_active--;

    l2cb.controller_xmit_window += p_lcb->link_xmit_quota;

    l2c_link_adjust_allocation();

    /* Check for ping outstanding */
    if (p_lcb->p_echo_rsp_cb)
    {
        tL2CA_ECHO_RSP_CB *p_cb = p_lcb->p_echo_rsp_cb;

        /* Zero out the callback in case app immediately calls us again */
        p_lcb->p_echo_rsp_cb = NULL;

        (*p_cb) (L2CAP_PING_RESULT_NO_LINK);
    }
}


/*******************************************************************************
**
** Function         l2cu_find_lcb_by_bd_addr
**
** Description      Look through all active LCBs for a match based on the
**                  remote BD address.
**
** Returns          pointer to matched LCB, or NULL if no match
**
*******************************************************************************/
tL2C_LCB  *l2cu_find_lcb_by_bd_addr (BD_ADDR p_bd_addr)
{
    int         xx;
    tL2C_LCB    *p_lcb = &l2cb.lcb_pool[0];

    for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p_lcb++)
    {
        if ((p_lcb->in_use) && (!memcmp (p_lcb->remote_bd_addr, p_bd_addr, BD_ADDR_LEN)))
        {
            return (p_lcb);
        }
    }

    /* If here, no match found */
    return (NULL);
}

/*******************************************************************************
**
** Function         l2cu_find_lcb_by_handle
**
** Description      Look through all active LCBs for a match based on the
**                  HCI handle.
**
** Returns          pointer to matched LCB, or NULL if no match
**
*******************************************************************************/
tL2C_LCB  *l2cu_find_lcb_by_handle (UINT16 handle)
{
    int         xx;
    tL2C_LCB    *p_lcb = &l2cb.lcb_pool[0];

    for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p_lcb++)
    {
        if ((p_lcb->in_use) && (p_lcb->handle == handle))
        {
            return (p_lcb);
        }
    }

    /* If here, no match found */
    return (NULL);
}

/*******************************************************************************
**
** Function         l2cu_get_conn_role
**
** Description      Determine the desired role (master or slave) of a link.
**
** Returns          HCI_ROLE_MASTER or HCI_ROLE_SLAVE
**
*******************************************************************************/
UINT8 l2cu_get_conn_role (tL2C_LCB *p_this_lcb)
{
    return l2cb.desire_role;
}

/*******************************************************************************
**
** Function         l2cu_build_header
**
** Description      Builds the L2CAP command packet header
**
** Returns          Pointer to allocated packet or NULL if no resources
**
*******************************************************************************/
BT_HDR *l2cu_build_header (UINT16 handle, UINT16 len, UINT8 cmd, UINT8 id)
{
    BT_HDR  *p_buf = (BT_HDR *)GKI_getpoolbuf (L2CAP_CMD_POOL_ID);
    UINT8   *p;

    if (!p_buf)
        return (NULL);

    p_buf->offset = L2CAP_SEND_CMD_OFFSET;
    p_buf->len = len + HCI_DATA_PREAMBLE_SIZE + L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;
    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET;

    /* Put in HCI header - handle + pkt boundary */
    UINT16_TO_STREAM (p, (handle | (L2CAP_PKT_START << L2CAP_PKT_TYPE_SHIFT)));

    UINT16_TO_STREAM (p, len + L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD);
    UINT16_TO_STREAM (p, len + L2CAP_CMD_OVERHEAD);
    UINT16_TO_STREAM (p, L2CAP_SIGNALLING_CID);

    /* Put in L2CAP command header */
    UINT8_TO_STREAM  (p, cmd);
    UINT8_TO_STREAM  (p, id);
    UINT16_TO_STREAM (p, len);

    return (p_buf);
}

/*******************************************************************************
**
** Function         l2cu_send_peer_cmd_reject
**
** Description      Build and send an L2CAP "command reject" message
**                  to the peer.
**
** Returns          void
**
*******************************************************************************/
void l2cu_send_peer_cmd_reject (tL2C_LCB *p_lcb, UINT16 reason, UINT8 rem_id,
                                UINT16 p1, UINT16 p2)
{
    UINT16  param_len;
    BT_HDR  *p_buf;
    UINT8   *p;

    /* Put in L2CAP packet header */
    if (reason == L2CAP_CMD_REJ_MTU_EXCEEDED)
        param_len = 2;
    else if (reason == L2CAP_CMD_REJ_INVALID_CID)
        param_len = 4;
    else
        param_len = 0;

    if ((p_buf = l2cu_build_header (p_lcb->handle, (UINT16) (L2CAP_CMD_REJECT_LEN + param_len), L2CAP_CMD_REJECT, rem_id)) == NULL )
    {
        L2CAP_TRACE_WARNING0 ("L2CAP - no buffer cmd_rej");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET + HCI_DATA_PREAMBLE_SIZE +
                               L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    UINT16_TO_STREAM (p, reason);

    if (param_len >= 2)
        UINT16_TO_STREAM (p, p1);

    if (param_len >= 4)
        UINT16_TO_STREAM (p, p2);

    l2c_link_check_send_pkts (p_lcb, NULL, p_buf);
}


/*******************************************************************************
**
** Function         l2cu_send_peer_connect_req
**
** Description      Build and send an L2CAP "connection request" message
**                  to the peer.
**
** Returns          void
**
*******************************************************************************/
void l2cu_send_peer_connect_req (tL2C_CCB *p_ccb)
{
    BT_HDR  *p_buf;
    UINT8   *p;

    /* Create an identifier for this packet */
    p_ccb->local_id = ++p_ccb->p_lcb->id;

    if ((p_buf = l2cu_build_header (p_ccb->p_lcb->handle, L2CAP_CONN_REQ_LEN, L2CAP_CMD_CONN_REQ,
                                    p_ccb->local_id)) == NULL)
    {
        L2CAP_TRACE_WARNING0 ("L2CAP - no buffer for conn_req");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET+HCI_DATA_PREAMBLE_SIZE +
        L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    UINT16_TO_STREAM (p, p_ccb->p_rcb->psm);
    UINT16_TO_STREAM (p, p_ccb->local_cid);

    l2c_link_check_send_pkts (p_ccb->p_lcb, NULL, p_buf);
}


/*******************************************************************************
**
** Function         l2cu_send_peer_connect_rsp
**
** Description      Build and send an L2CAP "connection response" message
**                  to the peer.
**
** Returns          void
**
*******************************************************************************/
void l2cu_send_peer_connect_rsp (tL2C_CCB *p_ccb, UINT16 result, UINT16 status)
{
    BT_HDR  *p_buf;
    UINT8   *p;

    if ((p_buf=l2cu_build_header(p_ccb->p_lcb->handle, L2CAP_CONN_RSP_LEN, L2CAP_CMD_CONN_RSP, p_ccb->remote_id)) == NULL)
    {
        L2CAP_TRACE_WARNING0 ("L2CAP - no buffer for conn_req");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET+HCI_DATA_PREAMBLE_SIZE +
        L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    UINT16_TO_STREAM (p, p_ccb->local_cid);
    UINT16_TO_STREAM (p, p_ccb->remote_cid);
    UINT16_TO_STREAM (p, result);
    UINT16_TO_STREAM (p, status);

    l2c_link_check_send_pkts (p_ccb->p_lcb, NULL, p_buf);
}


/*******************************************************************************
**
** Function         l2cu_reject_connection
**
** Description      Build and send an L2CAP "connection response neg" message
**                  to the peer. This function is called when there is no peer
**                  CCB (non-existant PSM or no resources).
**
** Returns          void
**
*******************************************************************************/
void l2cu_reject_connection (tL2C_LCB *p_lcb, UINT16 remote_cid, UINT8 rem_id, UINT16 result)
{
    BT_HDR  *p_buf;
    UINT8   *p;

    if ((p_buf = l2cu_build_header(p_lcb->handle, L2CAP_CONN_RSP_LEN, L2CAP_CMD_CONN_RSP, rem_id)) == NULL )
    {
        L2CAP_TRACE_WARNING0 ("L2CAP - no buffer for conn_req");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET+HCI_DATA_PREAMBLE_SIZE + L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    UINT16_TO_STREAM (p, 0);                    /* Local CID of 0   */
    UINT16_TO_STREAM (p, remote_cid);
    UINT16_TO_STREAM (p, result);
    UINT16_TO_STREAM (p, 0);                    /* Status of 0      */

    l2c_link_check_send_pkts (p_lcb, NULL, p_buf);
}

/*******************************************************************************
**
** Function         l2cu_send_peer_config_req
**
** Description      Build and send an L2CAP "configuration request" message
**                  to the peer.
**
** Returns          void
**
*******************************************************************************/
void l2cu_send_peer_config_req (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg)
{
    BT_HDR  *p_buf;
    UINT16  cfg_len=0;
    UINT8   *p;

    /* Create an identifier for this packet */
    p_ccb->local_id = ++p_ccb->p_lcb->id;

    if (p_cfg->mtu_present)
        cfg_len += L2CAP_CFG_MTU_OPTION_LEN + L2CAP_CFG_OPTION_OVERHEAD;
    if (p_cfg->flush_to_present)
        cfg_len += L2CAP_CFG_FLUSH_OPTION_LEN + L2CAP_CFG_OPTION_OVERHEAD;
    if (p_cfg->qos_present)
        cfg_len += L2CAP_CFG_QOS_OPTION_LEN + L2CAP_CFG_OPTION_OVERHEAD;
    if (p_cfg->fcr_present)
        cfg_len += L2CAP_CFG_FCR_OPTION_LEN + L2CAP_CFG_OPTION_OVERHEAD;

    if ((p_buf = l2cu_build_header (p_ccb->p_lcb->handle, (UINT16) (L2CAP_CONFIG_REQ_LEN + cfg_len),
        L2CAP_CMD_CONFIG_REQ, p_ccb->local_id)) == NULL )
    {
        L2CAP_TRACE_WARNING0 ("L2CAP - no buffer for conn_req");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET + HCI_DATA_PREAMBLE_SIZE +
                               L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    UINT16_TO_STREAM (p, p_ccb->remote_cid);
    UINT16_TO_STREAM (p, 0);                    /* Flags (no continuation) */

    /* Now, put the options */
    if (p_cfg->mtu_present)
    {
        UINT8_TO_STREAM  (p, L2CAP_CFG_TYPE_MTU);
        UINT8_TO_STREAM  (p, L2CAP_CFG_MTU_OPTION_LEN);
        UINT16_TO_STREAM (p, p_cfg->mtu);
    }
    if (p_cfg->flush_to_present)
    {
        UINT8_TO_STREAM  (p, L2CAP_CFG_TYPE_FLUSH_TOUT);
        UINT8_TO_STREAM  (p, L2CAP_CFG_FLUSH_OPTION_LEN);
        UINT16_TO_STREAM (p, p_cfg->flush_to);
    }
    if (p_cfg->qos_present)
    {
        UINT8_TO_STREAM  (p, L2CAP_CFG_TYPE_QOS);
        UINT8_TO_STREAM  (p, L2CAP_CFG_QOS_OPTION_LEN);
        UINT8_TO_STREAM  (p, p_cfg->qos.qos_flags);
        UINT8_TO_STREAM  (p, p_cfg->qos.service_type);
        UINT32_TO_STREAM (p, p_cfg->qos.token_rate);
        UINT32_TO_STREAM (p, p_cfg->qos.token_bucket_size);
        UINT32_TO_STREAM (p, p_cfg->qos.peak_bandwidth);
        UINT32_TO_STREAM (p, p_cfg->qos.latency);
        UINT32_TO_STREAM (p, p_cfg->qos.delay_variation);
    }
    if (p_cfg->fcr_present)
    {
        UINT8_TO_STREAM  (p, L2CAP_CFG_TYPE_FCR);
        UINT8_TO_STREAM  (p, L2CAP_CFG_FCR_OPTION_LEN);
        UINT8_TO_STREAM  (p, p_cfg->fcr.mode);
        UINT8_TO_STREAM  (p, p_cfg->fcr.tx_win_sz);
        UINT8_TO_STREAM  (p, p_cfg->fcr.max_transmit);
        UINT16_TO_STREAM (p, p_cfg->fcr.rtrans_tout);
        UINT16_TO_STREAM (p, p_cfg->fcr.mon_tout);
        UINT16_TO_STREAM (p, p_cfg->fcr.mps);
    }

    l2c_link_check_send_pkts (p_ccb->p_lcb, NULL, p_buf);
}

/*******************************************************************************
**
** Function         l2cu_send_peer_config_rsp
**
** Description      Build and send an L2CAP "configuration response" message
**                  to the peer.
**
** Returns          void
**
*******************************************************************************/
void l2cu_send_peer_config_rsp (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg)
{
    BT_HDR  *p_buf;
    UINT16  cfg_len = 0;
    UINT8   *p;

    /* Create an identifier for this packet */
    if (p_cfg->mtu_present)
        cfg_len += L2CAP_CFG_MTU_OPTION_LEN + L2CAP_CFG_OPTION_OVERHEAD;
    if (p_cfg->flush_to_present)
        cfg_len += L2CAP_CFG_FLUSH_OPTION_LEN + L2CAP_CFG_OPTION_OVERHEAD;
    if (p_cfg->qos_present)
        cfg_len += L2CAP_CFG_QOS_OPTION_LEN + L2CAP_CFG_OPTION_OVERHEAD;
    if (p_cfg->fcr_present)
        cfg_len += L2CAP_CFG_FCR_OPTION_LEN + L2CAP_CFG_OPTION_OVERHEAD;

    if ((p_buf = l2cu_build_header (p_ccb->p_lcb->handle, (UINT16) (L2CAP_CONFIG_RSP_LEN + cfg_len),
        L2CAP_CMD_CONFIG_RSP, p_ccb->remote_id)) == NULL )
    {
        L2CAP_TRACE_WARNING0 ("L2CAP - no buffer for conn_req");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET + HCI_DATA_PREAMBLE_SIZE +
                               L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    UINT16_TO_STREAM (p, p_ccb->remote_cid);
    UINT16_TO_STREAM (p, 0);                    /* Flags (no continuation) */
    UINT16_TO_STREAM (p, p_cfg->result);

    /* Now, put the options */
    if (p_cfg->mtu_present)
    {
        UINT8_TO_STREAM  (p, L2CAP_CFG_TYPE_MTU);
        UINT8_TO_STREAM  (p, L2CAP_CFG_MTU_OPTION_LEN);
        UINT16_TO_STREAM (p, p_cfg->mtu);
    }
    if (p_cfg->flush_to_present)
    {
        UINT8_TO_STREAM  (p, L2CAP_CFG_TYPE_FLUSH_TOUT);
        UINT8_TO_STREAM  (p, L2CAP_CFG_FLUSH_OPTION_LEN);
        UINT16_TO_STREAM (p, p_cfg->flush_to);
    }
    if (p_cfg->qos_present)
    {
        UINT8_TO_STREAM  (p, L2CAP_CFG_TYPE_QOS);
        UINT8_TO_STREAM  (p, L2CAP_CFG_QOS_OPTION_LEN);
        UINT8_TO_STREAM  (p, p_cfg->qos.qos_flags);
        UINT8_TO_STREAM  (p, p_cfg->qos.service_type);
        UINT32_TO_STREAM (p, p_cfg->qos.token_rate);
        UINT32_TO_STREAM (p, p_cfg->qos.token_bucket_size);
        UINT32_TO_STREAM (p, p_cfg->qos.peak_bandwidth);
        UINT32_TO_STREAM (p, p_cfg->qos.latency);
        UINT32_TO_STREAM (p, p_cfg->qos.delay_variation);
    }
    if (p_cfg->fcr_present)
    {
        UINT8_TO_STREAM  (p, L2CAP_CFG_TYPE_FCR);
        UINT8_TO_STREAM  (p, L2CAP_CFG_FCR_OPTION_LEN);
        UINT8_TO_STREAM  (p, p_cfg->fcr.mode);
        UINT8_TO_STREAM  (p, p_cfg->fcr.tx_win_sz);
        UINT8_TO_STREAM  (p, p_cfg->fcr.max_transmit);
        UINT16_TO_STREAM (p, p_cfg->fcr.rtrans_tout);
        UINT16_TO_STREAM (p, p_cfg->fcr.mon_tout);
        UINT16_TO_STREAM (p, p_cfg->fcr.mps);
    }

    l2c_link_check_send_pkts (p_ccb->p_lcb, NULL, p_buf);
}

/*******************************************************************************
**
** Function         l2cu_send_peer_config_rej
**
** Description      Build and send an L2CAP "configuration reject" message
**                  to the peer.
**
** Returns          void
**
*******************************************************************************/
void l2cu_send_peer_config_rej (tL2C_CCB *p_ccb, UINT8 *p_data, UINT16 data_len, UINT16 rej_len)
{
    BT_HDR  *p_buf = (BT_HDR *)GKI_getpoolbuf (L2CAP_CMD_POOL_ID);
    UINT16  len, cfg_len;
    UINT8   *p, *p_hci_len, *p_data_end;
    UINT8   cfg_code;

    if (!p_buf)
    {
        L2CAP_TRACE_WARNING0 ("L2CAP - no buffer for cfg_rej");
        return;
    }

    p_buf->offset = L2CAP_SEND_CMD_OFFSET;
    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET;

    /* Put in HCI header - handle + pkt boundary */
    UINT16_TO_STREAM (p, (p_ccb->p_lcb->handle | (L2CAP_PKT_START << L2CAP_PKT_TYPE_SHIFT)));

    /* Remember the HCI header length position, and save space for it */
    p_hci_len = p;
    p += 2;

    /* Put in L2CAP packet header */
    UINT16_TO_STREAM (p, L2CAP_CMD_OVERHEAD + L2CAP_CONFIG_RSP_LEN + rej_len);
    UINT16_TO_STREAM (p, L2CAP_SIGNALLING_CID);

    /* Put in L2CAP command header */
    UINT8_TO_STREAM  (p, L2CAP_CMD_CONFIG_RSP);
    UINT8_TO_STREAM  (p, p_ccb->remote_id);

    UINT16_TO_STREAM (p, L2CAP_CONFIG_RSP_LEN + rej_len);

    UINT16_TO_STREAM (p, p_ccb->remote_cid);
    UINT16_TO_STREAM (p, 0);                    /* Flags = 0 (no continuation) */
    UINT16_TO_STREAM (p, L2CAP_CFG_UNKNOWN_OPTIONS);

    /* Now, put the rejected options */
    p_data_end = p_data + data_len;
    while (p_data < p_data_end)
    {
        cfg_code = *p_data;
        cfg_len = *(p_data + 1);

        switch (cfg_code & 0x7F)
        {
            /* skip known options */
            case L2CAP_CFG_TYPE_MTU:
            case L2CAP_CFG_TYPE_FLUSH_TOUT:
            case L2CAP_CFG_TYPE_QOS:
                p_data += cfg_len + L2CAP_CFG_OPTION_OVERHEAD;
                break;

            /* unknown options; copy into rsp if not hints */
            default:
                /* sanity check option length */
                if ((cfg_len + L2CAP_CFG_OPTION_OVERHEAD) <= data_len)
                {
                    if ((cfg_code & 0x80) == 0)
                    {
                        memcpy(p, p_data, cfg_len + L2CAP_CFG_OPTION_OVERHEAD);
                        p += cfg_len + L2CAP_CFG_OPTION_OVERHEAD;
                    }
                    p_data += cfg_len + L2CAP_CFG_OPTION_OVERHEAD;
                }
                /* bad length; force loop exit */
                else
                {
                    p_data = p_data_end;
                }
                break;
        }
    }

    len = (UINT16) (p - p_hci_len - 2);
    UINT16_TO_STREAM (p_hci_len, len);

    p_buf->len = len + 4;

    l2c_link_check_send_pkts (p_ccb->p_lcb, p_ccb, p_buf);
}

/*******************************************************************************
**
** Function         l2cu_send_peer_disc_req
**
** Description      Build and send an L2CAP "disconnect request" message
**                  to the peer.
**
** Returns          void
**
*******************************************************************************/
void l2cu_send_peer_disc_req (tL2C_CCB *p_ccb)
{
    BT_HDR  *p_buf;
    UINT8   *p;

    /* Create an identifier for this packet */
    p_ccb->local_id = ++p_ccb->p_lcb->id;

    if ((p_buf = l2cu_build_header (p_ccb->p_lcb->handle, L2CAP_DISC_REQ_LEN, L2CAP_CMD_DISC_REQ,
                                    p_ccb->local_id)) == NULL)
    {
        L2CAP_TRACE_WARNING0 ("L2CAP - no buffer for conn_req");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET + HCI_DATA_PREAMBLE_SIZE +
                               L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    UINT16_TO_STREAM (p, p_ccb->remote_cid);
    UINT16_TO_STREAM (p, p_ccb->local_cid);

    p_buf->layer_specific = 0;
    GKI_enqueue (&p_ccb->p_lcb->link_xmit_data_q, p_buf);

    l2c_link_check_send_pkts (p_ccb->p_lcb, NULL, NULL);
}


/*******************************************************************************
**
** Function         l2cu_send_peer_disc_rsp
**
** Description      Build and send an L2CAP "disconnect response" message
**                  to the peer.
**
** Returns          void
**
*******************************************************************************/
void l2cu_send_peer_disc_rsp (tL2C_LCB *p_lcb, UINT8 remote_id, UINT16 local_cid,
                              UINT16 remote_cid)
{
    BT_HDR  *p_buf;
    UINT8   *p;

    if ((p_buf = l2cu_build_header (p_lcb->handle, L2CAP_DISC_RSP_LEN, L2CAP_CMD_DISC_RSP, remote_id)) == NULL)
    {
        L2CAP_TRACE_WARNING0 ("L2CAP - no buffer for conn_req");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET + HCI_DATA_PREAMBLE_SIZE +
                               L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    UINT16_TO_STREAM (p, local_cid);
    UINT16_TO_STREAM (p, remote_cid);

    p_buf->layer_specific = 0;
    GKI_enqueue (&p_lcb->link_xmit_data_q, p_buf);

    l2c_link_check_send_pkts (p_lcb, NULL, NULL);
}


/*******************************************************************************
**
** Function         l2cu_send_peer_echo_req
**
** Description      Build and send an L2CAP "echo request" message
**                  to the peer. Note that we do not currently allow
**                  data in the echo request.
**
** Returns          void
**
*******************************************************************************/
void l2cu_send_peer_echo_req (tL2C_LCB *p_lcb, UINT8 *p_data, UINT16 data_len)
{
    BT_HDR  *p_buf;
    UINT8   *p;

    if ((p_buf = l2cu_build_header(p_lcb->handle, (UINT16) (L2CAP_ECHO_REQ_LEN + data_len), L2CAP_CMD_ECHO_REQ, ++p_lcb->id)) == NULL)
    {
        L2CAP_TRACE_WARNING0 ("L2CAP - no buffer for echo_req");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET + HCI_DATA_PREAMBLE_SIZE + L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    if (data_len)
    {
        ARRAY_TO_STREAM  (p, p_data, data_len);
    }

    l2c_link_check_send_pkts (p_lcb, NULL, p_buf);
}


/*******************************************************************************
**
** Function         l2cu_send_peer_echo_rsp
**
** Description      Build and send an L2CAP "echo response" message
**                  to the peer.
**
** Returns          void
**
*******************************************************************************/
void l2cu_send_peer_echo_rsp (tL2C_LCB *p_lcb, UINT8 id, UINT8 *p_data, UINT16 data_len)
{
    BT_HDR  *p_buf;
    UINT8   *p;
    UINT16   maxlen;

    /* Don't return data if it does not fit in ACL and L2CAP MTU */
    maxlen = (GKI_BUF2_SIZE > btu_cb.hcit_acl_pkt_size) ?
               btu_cb.hcit_acl_data_size : (UINT16)GKI_BUF2_SIZE;
    maxlen -= (UINT16)(HCI_DATA_PREAMBLE_SIZE + L2CAP_PKT_OVERHEAD +
                L2CAP_CMD_OVERHEAD + L2CAP_ECHO_RSP_LEN);

    if (data_len > maxlen)
        data_len = 0;

    if ((p_buf = l2cu_build_header (p_lcb->handle, (UINT16)(L2CAP_ECHO_RSP_LEN + data_len), L2CAP_CMD_ECHO_RSP, id)) == NULL)
    {
        L2CAP_TRACE_WARNING0 ("L2CAP - no buffer for conn_req");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET + HCI_DATA_PREAMBLE_SIZE +
                               L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    if (data_len)
    {
        ARRAY_TO_STREAM  (p, p_data, data_len);
    }

    l2c_link_check_send_pkts (p_lcb, NULL, p_buf);
}

/*******************************************************************************
**
** Function         l2cu_send_peer_info_rsp
**
** Description      Build and send an L2CAP "info response" message
**                  to the peer.
**
** Returns          void
**
*******************************************************************************/
void l2cu_send_peer_info_rsp (tL2C_LCB *p_lcb, UINT8 remote_id, UINT16 info_type)
{
    BT_HDR  *p_buf;
    UINT8   *p;
    UINT16   len = L2CAP_INFO_RSP_LEN;

    if ((p_buf = l2cu_build_header(p_lcb->handle, len, L2CAP_CMD_INFO_RSP, remote_id)) == NULL)
    {
        L2CAP_TRACE_WARNING0 ("L2CAP - no buffer for conn_req");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET+HCI_DATA_PREAMBLE_SIZE +
        L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    UINT16_TO_STREAM (p, info_type);
    UINT16_TO_STREAM (p, L2CAP_INFO_RESP_RESULT_NOT_SUPPORTED);

    l2c_link_check_send_pkts (p_lcb, NULL, p_buf);
}

/*******************************************************************************
**
** Function         l2cu_allocate_ccb
**
** Description      This function allocates a Channel Control Block and
**                  attaches it to a link control block. The local CID
**                  is also assigned.
**
** Returns          pointer to CCB, or NULL if none
**
*******************************************************************************/
tL2C_CCB *l2cu_allocate_ccb (tL2C_LCB *p_lcb)
{
    tL2C_CCB *p_ccb;
    if (!l2cb.p_free_ccb_first)
        return (NULL);
    p_ccb = l2cb.p_free_ccb_first;
    l2cb.p_free_ccb_first = p_ccb->p_next_ccb;
    p_ccb->in_use = TRUE;
    p_ccb->local_cid = L2CAP_BASE_APPL_CID + (UINT16)(p_ccb - l2cb.ccb_pool);
    p_ccb->p_lcb = p_lcb;
    if (!p_lcb->ccb_queue.p_first_ccb)
    {
        p_lcb->ccb_queue.p_first_ccb = p_lcb->ccb_queue.p_last_ccb = p_ccb;
        p_ccb->p_prev_ccb = p_ccb->p_next_ccb = NULL;
    }
    else
    {
        p_ccb->p_next_ccb = NULL;
        p_ccb->p_prev_ccb = p_lcb->ccb_queue.p_last_ccb;
        p_lcb->ccb_queue.p_last_ccb->p_next_ccb = p_ccb;
        p_lcb->ccb_queue.p_last_ccb = p_ccb;
    }
    p_ccb->flush_timeout = L2CAP_DEFAULT_FLUSH_TO;
    p_ccb->peer_mtu = L2CAP_DEFAULT_MTU;
    p_ccb->our_mtu = L2CAP_DEFAULT_MTU;
    p_ccb->our_qos.service_type = L2CAP_DEFAULT_SERV_TYPE;
    p_ccb->peer_qos.service_type = L2CAP_DEFAULT_SERV_TYPE;
    p_ccb->our_qos.token_rate = L2CAP_DEFAULT_TOKEN_RATE;
    p_ccb->peer_qos.token_rate = L2CAP_DEFAULT_TOKEN_RATE;
    p_ccb->our_qos.token_bucket_size = L2CAP_DEFAULT_BUCKET_SIZE;
    p_ccb->peer_qos.token_bucket_size = L2CAP_DEFAULT_BUCKET_SIZE;
    p_ccb->our_qos.peak_bandwidth = L2CAP_DEFAULT_PEAK_BANDWIDTH;
    p_ccb->peer_qos.peak_bandwidth = L2CAP_DEFAULT_PEAK_BANDWIDTH;
    p_ccb->our_qos.latency = L2CAP_DEFAULT_LATENCY;
    p_ccb->peer_qos.latency = L2CAP_DEFAULT_LATENCY;
    p_ccb->our_qos.delay_variation = L2CAP_DEFAULT_DELAY;
    p_ccb->peer_qos.delay_variation = L2CAP_DEFAULT_DELAY;
    p_ccb->config_done = 0;
    p_ccb->chnl_state = CST_CLOSED;
    p_ccb->flags = 1;
    p_ccb->timer_entry.param = (TIMER_PARAM_TYPE)p_ccb;
    return (p_ccb);
}

/*******************************************************************************
**
** Function         l2cu_release_ccb
**
** Description      This function releases a Channel Control Block. The timer
**                  is stopped, any attached buffers freed, and the CCB is removed
**                  from the link control block.
**
** Returns          void
**
*******************************************************************************/
void l2cu_release_ccb (tL2C_CCB *p_ccb)
{
    tL2C_LCB    *p_lcb = p_ccb->p_lcb;
    UINT16      timeout;
    UINT8       rc;

    /* If already released, could be race condition */
    if (!p_ccb->in_use)
        return;

    p_ccb->in_use = FALSE;

    /* Stop the timer */
    btu_stop_timer (&p_ccb->timer_entry);

    while (p_ccb->xmit_hold_q.p_first)
        GKI_freebuf (GKI_dequeue (&p_ccb->xmit_hold_q));

    /* Delink the CCB from the LCB */
    p_ccb->p_lcb = NULL;

    if (p_lcb->ccb_queue.p_first_ccb == p_ccb)
    {
        p_lcb->ccb_queue.p_first_ccb = p_ccb->p_next_ccb;

        if (p_lcb->ccb_queue.p_first_ccb)
            p_lcb->ccb_queue.p_first_ccb->p_prev_ccb = NULL;
    }
    else if (p_lcb->ccb_queue.p_last_ccb == p_ccb)
    {
        p_lcb->ccb_queue.p_last_ccb = p_ccb->p_prev_ccb;
        p_lcb->ccb_queue.p_last_ccb->p_next_ccb = NULL;
    }
    else
    {
        p_ccb->p_prev_ccb->p_next_ccb = p_ccb->p_next_ccb;
        p_ccb->p_next_ccb->p_prev_ccb = p_ccb->p_prev_ccb;
    }

    /* Put the CCB back on the free pool */
    if (!l2cb.p_free_ccb_first)
    {
        l2cb.p_free_ccb_first = p_ccb;
        l2cb.p_free_ccb_last  = p_ccb;
        p_ccb->p_next_ccb     = NULL;
        p_ccb->p_prev_ccb     = NULL;
    }
    else
    {
        p_ccb->p_next_ccb  = NULL;
        p_ccb->p_prev_ccb  = l2cb.p_free_ccb_last;
        l2cb.p_free_ccb_last->p_next_ccb = p_ccb;
        l2cb.p_free_ccb_last  = p_ccb;
    }

    /* If no channels on the connection, start idle timeout */
    if ((p_lcb->in_use) && (p_lcb->link_state == LST_CONNECTED) && (!p_lcb->ccb_queue.p_first_ccb))
    {
        timeout = p_lcb->idle_timeout;

        if (!timeout)
        {
            rc = btm_sec_disconnect (p_lcb->handle, HCI_ERR_PEER_USER);

            if (rc == BTM_CMD_STARTED)
            {
                p_lcb->link_state = LST_DISCONNECTING;
                timeout = L2CAP_LINK_DISCONNECT_TOUT;
            }
            else if (rc == BTM_SUCCESS)
            {
                p_lcb->link_state = LST_DISCONNECTING;
                timeout = 0xFFFF;
            }
            else
            {
                /* probably no buffer to send disconnect */
                timeout = BT_1SEC_TIMEOUT;
            }
        }

        if (timeout != 0xFFFF)
        {
            btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, timeout);
        }
    }
}

/*******************************************************************************
**
** Function         l2cu_find_ccb_by_cid
**
** Description      Look through all active CCBs on a link for a match based
**                  on the local CID. If passed the link pointer is NULL, all
**                  active links are searched.
**
** Returns          pointer to matched CCB, or NULL if no match
**
*******************************************************************************/
tL2C_CCB *l2cu_find_ccb_by_cid (tL2C_LCB *p_lcb, UINT16 local_cid)
{
    tL2C_CCB    *p_ccb = NULL;
    UINT16      xx;

    if (local_cid >= L2CAP_BASE_APPL_CID)
    {
        xx = local_cid - L2CAP_BASE_APPL_CID;
        p_ccb = &l2cb.ccb_pool[xx];

        if (!p_ccb->in_use)
            p_ccb = NULL;
        else if (p_lcb && p_lcb != p_ccb->p_lcb)
            p_ccb = NULL;
    }

    return (p_ccb);
}

/*******************************************************************************
**
** Function         l2cu_allocate_rcb
**
** Description      Look for an unused RCB
**
** Returns          pointer to allocated rcb or NULL if none found
**
*******************************************************************************/
tL2C_RCB *l2cu_allocate_rcb (UINT16 psm)
{
    tL2C_RCB    *p_rcb = &l2cb.rcb_pool[0];
    UINT16      xx;

    for (xx = 0; xx < MAX_L2CAP_CLIENTS; xx++, p_rcb++)
    {
        if (!p_rcb->in_use)
        {
            p_rcb->in_use = TRUE;
            p_rcb->psm    = psm;
            return (p_rcb);
        }
    }

    /* If here, no free RCB found */
    return (NULL);
}

/*******************************************************************************
**
** Function         l2cu_release_rcb
**
** Description      Mark an RCB as no longer in use
**
** Returns          void
**
*******************************************************************************/
void l2cu_release_rcb (tL2C_RCB *p_rcb)
{
    p_rcb->in_use = FALSE;
    p_rcb->psm    = 0;
}

/*******************************************************************************
**
** Function         l2cu_find_rcb_by_psm
**
** Description      Look through all active RCBs for a match based on the
**                  PSM.
**
** Returns          pointer to the matched RCB, or NULL if no match
**
*******************************************************************************/
tL2C_RCB *l2cu_find_rcb_by_psm (UINT16 psm)
{
    tL2C_RCB    *p_rcb = &l2cb.rcb_pool[0];
    UINT16      xx;

    for (xx = 0; xx < MAX_L2CAP_CLIENTS; xx++, p_rcb++)
    {
        if ((p_rcb->in_use) && (p_rcb->psm == psm))
        {
            return (p_rcb);
        }
    }

    /* If here, no match found */
    return (NULL);
}

/*******************************************************************************
**
** Function         l2cu_process_peer_cfg_req
**
** Description      This function is called when the peer sends us a "config request"
**                  message. It extracts the configuration of interest and saves
**                  it in the CCB.
**
**                  Note:  Negotiation of the FCR channel type is handled internally,
**                         all others are passed to the upper layer.
**
** Returns          UINT8 - L2CAP_PEER_CFG_OK if passed, otherwise L2CAP_PEER_CFG_UNACCEPTABLE
**
*******************************************************************************/
UINT8 l2cu_process_peer_cfg_req (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg)
{
    BOOLEAN  mtu_ok      = TRUE;
    BOOLEAN  qos_type_ok = TRUE;
    BOOLEAN  flush_to_ok = TRUE;
    UINT8    status;
    BOOLEAN  all_ok;

    /* Save the MTU that our peer can receive */
    if (p_cfg->mtu_present)
    {
        /* Make sure MTU is at least the minimum */
        if (p_cfg->mtu >= L2CAP_MIN_MTU)
        {
            /* Save the accepted value in case of renegotiation */
            p_ccb->peer_mtu = p_cfg->mtu;

            if (p_ccb->peer_mtu > L2CAP_MTU_SIZE)
            {
                p_cfg->mtu = L2CAP_MTU_SIZE;
                p_ccb->peer_mtu = p_cfg->mtu;
            }
        }
        else    /* Illegal MTU value */
        {
            p_cfg->mtu = L2CAP_MIN_MTU;
            mtu_ok     = FALSE;
        }
    }

    /* Verify that the flush timeout is a valid value (0 is illegal) */
    if (p_cfg->flush_to_present)
    {
        if (!p_cfg->flush_to)
        {
            p_cfg->flush_to = 0xFFFF;   /* Infinite retransmissions (spec default) */
            flush_to_ok     = FALSE;
        }
    }

    /* Save the QOS settings the the peer is using */
    if (p_cfg->qos_present)
    {
        /* Make sure service type is not a reserved value; otherwise let upper
           layer decide if acceptable
        */
        if (p_cfg->qos.service_type <= GUARANTEED)
        {
            p_ccb->peer_qos = p_cfg->qos;
        }
        else    /* Illegal service type value */
        {
            p_cfg->qos.service_type = BEST_EFFORT;
            qos_type_ok             = FALSE;
        }
    }

    /* Return any unacceptable parameters */
    status = L2CAP_PEER_CFG_UNACCEPTABLE;
    all_ok = FALSE;

    if (mtu_ok && flush_to_ok && qos_type_ok)
        all_ok = TRUE;

    if (all_ok)
        status = L2CAP_PEER_CFG_OK;

    if (status)
        return (status);

    p_cfg->result = L2CAP_CFG_UNACCEPTABLE_PARAMS;

    if (mtu_ok)
        p_cfg->mtu_present = FALSE;
    if (flush_to_ok)
        p_cfg->flush_to_present = FALSE;
    if (qos_type_ok)
        p_cfg->qos_present = FALSE;

    p_cfg->fcr_present = FALSE;

    return (status);
}


/*******************************************************************************
**
** Function         l2cu_process_peer_cfg_rsp
**
** Description      This function is called when the peer sends us a "config response"
**                  message. It extracts the configuration of interest and saves
**                  it in the CCB.
**
** Returns          void
**
*******************************************************************************/
void l2cu_process_peer_cfg_rsp (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg)
{
    /* If we wanted QoS and the peer sends us a positive response with QoS, use his values */
    if (p_cfg->qos_present)
        p_ccb->our_qos = p_cfg->qos;
}


/*******************************************************************************
**
** Function         l2cu_process_our_cfg_req
**
** Description      This function is called when we send a "config request"
**                  message. It extracts the configuration of interest and saves
**                  it in the CCB.
**
** Returns          void
**
*******************************************************************************/
void l2cu_process_our_cfg_req (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg)
{
    tL2C_LCB    *p_lcb;
    UINT16      hci_flush_to;
    BT_HDR      *p_buf;

    /* Save the MTU that we will accept, in case of renegotiation */
    if (p_cfg->mtu_present)
    {
        p_ccb->our_mtu = p_cfg->mtu;

        if (p_ccb->our_mtu > L2CAP_MTU_SIZE)
        {
            p_cfg->mtu = L2CAP_MTU_SIZE;
            p_ccb->our_mtu = p_cfg->mtu;
        }
    }

    /* If we wanted QoS and the peer sends us a positive response with QoS, use his values */
    if (p_cfg->qos_present)
        p_ccb->our_qos = p_cfg->qos;

    /* Save the flush timeout, and set it in the controller if it is shorter than the link's */
    if ((p_cfg->flush_to_present) && (p_cfg->flush_to != 0))
    {
        p_ccb->flush_timeout = p_cfg->flush_to;

        p_lcb = p_ccb->p_lcb;

        if (p_cfg->flush_to < p_lcb->link_flush_tout)
        {
            p_lcb->link_flush_tout = p_cfg->flush_to;

            /* If the timeout is within range of HCI, set the flush timeout */
            if (p_cfg->flush_to <= ((HCI_MAX_AUTO_FLUSH_TOUT * 5) / 8))
            {
                /* Convert flush timeout to 0.625 ms units, with round */
                hci_flush_to = ((p_cfg->flush_to * 8) + 3) / 5;
                if ((p_buf = (BT_HDR *)GKI_getpoolbuf (HCI_CMD_POOL_ID)) != NULL)
                    btsnd_hcic_write_auto_flush_tout (p_buf, p_lcb->handle, hci_flush_to);
            }
        }
    }
}

/*******************************************************************************
**
** Function         l2cu_process_our_cfg_rsp
**
** Description      This function is called when we send the peer a "config response"
**                  message. It extracts the configuration of interest and saves
**                  it in the CCB.
**
** Returns          void
**
*******************************************************************************/
void l2cu_process_our_cfg_rsp (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg)
{
    /* If peer wants QoS, we are allowed to change the values in a positive response */
    if (p_cfg->qos_present)
        p_ccb->peer_qos = p_cfg->qos;
}

/*******************************************************************************
**
** Function         l2cu_device_reset
**
** Description      This function is called when reset of the device is
**                  completed.  For all active connection simulate HCI_DISC
**
** Returns          void
**
*******************************************************************************/
void l2cu_device_reset (void)
{
    int         xx;
    tL2C_LCB    *p_lcb = &l2cb.lcb_pool[0];

    for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p_lcb++)
    {
        if ((p_lcb->in_use) && (p_lcb->handle != HCI_INVALID_HANDLE))
        {
            l2c_link_hci_disc_comp (p_lcb->handle, (UINT8) -1);
        }
    }
}

/*******************************************************************************
**
** Function         l2cu_create_conn
**
** Description      This function initiates an acl connection via HCI
**
** Returns          TRUE if successful, FALSE if gki get buffer fails.
**
*******************************************************************************/
BOOLEAN l2cu_create_conn (tL2C_LCB *p_lcb)
{
    int             xx;
    tL2C_LCB        *p_lcb_cur = &l2cb.lcb_pool[0];
    BOOLEAN         is_sco_active;

    p_lcb->link_state = LST_CONNECTING;

    /* If there is a connection where we perform as a slave, try to switch roles
       for this connection */
    for (xx = 0, p_lcb_cur = &l2cb.lcb_pool[0]; xx < MAX_L2CAP_LINKS; xx++, p_lcb_cur++)
    {
        if (p_lcb_cur == p_lcb)
            continue;

        if ((p_lcb_cur->in_use) && (p_lcb_cur->link_role == HCI_ROLE_SLAVE))
        {
            /* Check if there is any SCO Active on this BD Address */
            is_sco_active = btm_is_sco_active_by_bdaddr(p_lcb_cur->remote_bd_addr);

            L2CAP_TRACE_API1 ("l2cu_create_conn - btm_is_sco_active_by_bdaddr() is_sco_active = %s", \
                (is_sco_active == TRUE) ? "TRUE":"FALSE");

            if (is_sco_active == TRUE)
                continue; /* No Master Slave switch not allowed when SCO Active */

            if (HCI_SWITCH_SUPPORTED(btm_cb.devcb.local_features))
            {
                /* mark this lcb waiting for switch to be completed and
                   start switch on the other one */
                p_lcb->link_state = LST_CONNECTING_WAIT_SWITCH;
                p_lcb->link_role  = HCI_ROLE_MASTER;

                BTM_SwitchRole (p_lcb_cur->remote_bd_addr, HCI_ROLE_MASTER, NULL);

                btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, L2CAP_LINK_ROLE_SWITCH_TOUT);
                return (TRUE);
            }
        }
    }

    return (l2cu_create_conn_after_switch (p_lcb));
}

/*******************************************************************************
**
** Function         l2cu_create_conn_after_switch
**
** Description      This function initiates an acl connection via HCI
**                  If switch required to create connection it is already done.
**
** Returns          TRUE if successful, FALSE if gki get buffer fails.
**
*******************************************************************************/
BOOLEAN l2cu_create_conn_after_switch (tL2C_LCB *p_lcb)
{
    UINT8            allow_switch;
    tBTM_INQ_INFO    *p_inq_info;
    UINT8            page_scan_rep_mode;
    UINT8            page_scan_mode;
    UINT16           clock_offset;
    UINT8            *p_features;

    p_features = BTM_ReadLocalFeatures();

    allow_switch = (HCI_SWITCH_SUPPORTED(p_features)) ? HCI_CR_CONN_ALLOW_SWITCH : HCI_CR_CONN_NOT_ALLOW_SWITCH;

    p_lcb->link_state = LST_CONNECTING;

    /* Check with the BT manager if details about remote device are known */
    if ((p_inq_info = BTM_InqDbRead(p_lcb->remote_bd_addr)) != NULL)
    {
        page_scan_rep_mode = p_inq_info->results.page_scan_rep_mode;
        page_scan_mode = p_inq_info->results.page_scan_mode;
        clock_offset = (UINT16)(p_inq_info->results.clock_offset | BTM_CLOCK_OFFSET_VALID);
    }
    else
    {
        /* No info known. Use default settings */
        page_scan_rep_mode = HCI_PAGE_SCAN_REP_MODE_R1;
        page_scan_mode = HCI_MANDATARY_PAGE_SCAN_MODE;

        clock_offset = 0;
    }

    if (!btsnd_hcic_create_conn (p_lcb->remote_bd_addr,
                                 HCI_PKT_TYPES_MASK_DM1 + HCI_PKT_TYPES_MASK_DH1,
                                 page_scan_rep_mode,
                                 page_scan_mode,
                                 clock_offset,
                                 allow_switch))

    {
        L2CAP_TRACE_ERROR0 ("L2CAP - no buffer for l2cu_create_conn");
        l2cu_release_lcb (p_lcb);
        return (FALSE);
    }

    btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK,
                     L2CAP_LINK_CONNECT_TOUT);

    return (TRUE);
}


/*******************************************************************************
**
** Function         l2cu_find_lcb_by_state
**
** Description      Look through all active LCBs for a match based on the
**                  LCB state.
**
** Returns          pointer to first matched LCB, or NULL if no match
**
*******************************************************************************/
tL2C_LCB *l2cu_find_lcb_by_state (tL2C_LINK_STATE state)
{
    UINT16      i;
    tL2C_LCB    *p_lcb = &l2cb.lcb_pool[0];

    for (i = 0; i < MAX_L2CAP_LINKS; i++, p_lcb++)
    {
        if ((p_lcb->in_use) && (p_lcb->link_state == state))
        {
            return (p_lcb);
        }
    }

    /* If here, no match found */
    return (NULL);
}


/*******************************************************************************
**
** Function         l2cu_lcb_disconnecting
**
** Description      On each active lcb, check if the lcb is in disconnecting
**                  state, or if there are no ccb's on the lcb (implying
                    idle timeout is running), or if last ccb on the link
                    is in disconnecting state.
**
** Returns          TRUE if any of above conditions met, FALSE otherwise
**
*******************************************************************************/
BOOLEAN l2cu_lcb_disconnecting (void)
{
    tL2C_LCB    *p_lcb;
    tL2C_CCB    *p_ccb;
    UINT16      i;
    BOOLEAN     status = FALSE;

    p_lcb = &l2cb.lcb_pool[0];

    for (i = 0; i < MAX_L2CAP_LINKS; i++, p_lcb++)
    {
        if (p_lcb->in_use)
        {
            /* no ccbs on lcb, or lcb is in disconnecting state */
            if ((!p_lcb->ccb_queue.p_first_ccb) || (p_lcb->link_state == LST_DISCONNECTING))
            {
                status = TRUE;
                break;
            }
            /* only one ccb left on lcb */
            else if (p_lcb->ccb_queue.p_first_ccb == p_lcb->ccb_queue.p_last_ccb)
            {
                p_ccb = p_lcb->ccb_queue.p_first_ccb;

                if ((p_ccb->in_use) &&
                    ((p_ccb->chnl_state == CST_W4_L2CAP_DISCONNECT_RSP) ||
                     (p_ccb->chnl_state == CST_W4_L2CA_DISCONNECT_RSP)))
                {
                    status = TRUE;
                    break;
                }
            }
        }
    }
    return status;
}

#if 0
/* Functions not present in the Wii (older) BTE; kept for reference. */
/*******************************************************************************
**
** Function         l2cu_update_lcb_4_bonding
**
** Description      Mark the lcb for bonding. Used when bonding takes place on
**                  an existing ACL connection.  (Pre-Lisbon devices)
**
** Returns          Nothing
**
*******************************************************************************/
void l2cu_update_lcb_4_bonding (BD_ADDR p_bd_addr, BOOLEAN is_bonding)
{
    tL2C_LCB    *p_lcb = l2cu_find_lcb_by_bd_addr (p_bd_addr);

    if (p_lcb)
    {
        L2CAP_TRACE_DEBUG3 ("l2cu_update_lcb_4_bonding  BDA: %08x%04x is_bonding: %d",
                          (p_bd_addr[0]<<24)+(p_bd_addr[1]<<16)+(p_bd_addr[2]<<8)+p_bd_addr[3],
                          (p_bd_addr[4]<<8)+p_bd_addr[5], is_bonding);
        p_lcb->is_bonding = is_bonding;
    }
}

/*******************************************************************************
**
** Function         l2cu_adj_id
**
** Description      Checks for valid ID based on specified mask
**                  and adjusts the id if invalid.
**
** Returns          void
**
*******************************************************************************/
void l2cu_adj_id (tL2C_LCB *p_lcb, UINT8 adj_mask)
{
#if (L2CAP_ENHANCED_FEATURES != 0)
    if ((adj_mask & L2CAP_ADJ_BRCM_ID) && p_lcb->id == L2CAP_FEATURE_REQ_ID)
    {
        p_lcb->id++;
    }
#endif

    if ((adj_mask & L2CAP_ADJ_ZERO_ID) && !p_lcb->id)
    {
        p_lcb->id++;
    }
}

/*******************************************************************************
**
** Function         l2cu_send_peer_info_req
**
** Description      Build and send an L2CAP "info request" message
**                  to the peer.
** Returns          void
**
*******************************************************************************/
void l2cu_send_peer_info_req (tL2C_LCB *p_lcb, UINT16 info_type)
{
    BT_HDR  *p_buf;
    UINT8   *p;

    /* check for wrap and/or BRCM ID */
    p_lcb->id++;
    l2cu_adj_id(p_lcb, L2CAP_ADJ_ID);

    if ((p_buf = l2cu_build_header(p_lcb, 2, L2CAP_CMD_INFO_REQ, p_lcb->id)) == NULL)
    {
        L2CAP_TRACE_WARNING0 ("L2CAP - no buffer for info_req");
        return;
    }

    L2CAP_TRACE_EVENT1 ("l2cu_send_peer_info_req: type 0x%04x", info_type);

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET+HCI_DATA_PREAMBLE_SIZE +
        L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    UINT16_TO_STREAM (p, info_type);

    p_lcb->w4_info_rsp = TRUE;
    btu_start_timer (&p_lcb->info_timer_entry, BTU_TTYPE_L2CAP_INFO, L2CAP_WAIT_INFO_RSP_TOUT);

    l2c_link_check_send_pkts (p_lcb, NULL, p_buf);
}

/******************************************************************************
**
** Function         l2cu_enqueue_ccb
**
** Description      queue CCB by priority. The first CCB is highest priority and
**                  is served at first. The CCB is queued to an LLCB or an LCB.
**
** Returns          None
**
*******************************************************************************/
void l2cu_enqueue_ccb (tL2C_CCB *p_ccb)
{
    tL2C_CCB        *p_ccb1;
    tL2C_CCB_Q      *p_q = NULL;

    /* Find out which queue the channel is on
    */
    if (p_ccb->p_lcb != NULL)
        p_q = &p_ccb->p_lcb->ccb_queue;

    if ( (!p_ccb->in_use) || (p_q == NULL) )
    {
        L2CAP_TRACE_ERROR3 ("l2cu_enqueue_ccb  CID: 0x%04x ERROR in_use: %u  p_lcb: 0x%08x",
                            p_ccb->local_cid, p_ccb->in_use, p_ccb->p_lcb);
        return;
    }

    L2CAP_TRACE_DEBUG2 ("l2cu_enqueue_ccb CID: 0x%04x  priority: %d",
                        p_ccb->local_cid, p_ccb->ccb_priority);

    /* If the queue is empty, we go at the front */
    if (!p_q->p_first_ccb)
    {
        p_q->p_first_ccb  = p_q->p_last_ccb   = p_ccb;
        p_ccb->p_next_ccb = p_ccb->p_prev_ccb = NULL;
    }
    else
    {
        p_ccb1 = p_q->p_first_ccb;

        while (p_ccb1 != NULL)
        {
            /* Insert new ccb at the end of the same priority. Lower number, higher priority */
            if (p_ccb->ccb_priority < p_ccb1->ccb_priority)
            {
                /* Are we at the head of the queue ? */
                if (p_ccb1 == p_q->p_first_ccb)
                    p_q->p_first_ccb = p_ccb;
                else
                    p_ccb1->p_prev_ccb->p_next_ccb  = p_ccb;

                p_ccb->p_next_ccb  = p_ccb1;
                p_ccb->p_prev_ccb  = p_ccb1->p_prev_ccb;
                p_ccb1->p_prev_ccb = p_ccb;
                break;
            }

            p_ccb1 = p_ccb1->p_next_ccb;
        }

        /* If we are lower then anyone in the list, we go at the end */
        if (!p_ccb1)
        {
            /* add new ccb at the end of the list */
            p_q->p_last_ccb->p_next_ccb = p_ccb;

            p_ccb->p_next_ccb   = NULL;
            p_ccb->p_prev_ccb   = p_q->p_last_ccb;
            p_q->p_last_ccb = p_ccb;
        }
    }

#if (L2CAP_ROUND_ROBIN_CHANNEL_SERVICE == TRUE)
    /* Adding CCB into round robin service table of its LCB */
    if (p_ccb->p_lcb != NULL)
    {
        /* if this is the first channel in this priority group */
        if (p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].num_ccb == 0 )
        {
        	/* Set the first channel to this CCB */
            p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_first_ccb = p_ccb;
        	/* Set the next serving channel in this group to this CCB */
            p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_serve_ccb = p_ccb;
        	/* Initialize quota of this priority group based on its priority */
            p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].quota = L2CAP_GET_PRIORITY_QUOTA(p_ccb->ccb_priority);
        }
        /* increase number of channels in this group */
        p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].num_ccb++;
    }
#endif

}

/******************************************************************************
**
** Function         l2cu_dequeue_ccb
**
** Description      dequeue CCB from a queue
**
** Returns          -
**
*******************************************************************************/
void l2cu_dequeue_ccb (tL2C_CCB *p_ccb)
{
    tL2C_CCB_Q      *p_q = NULL;

    L2CAP_TRACE_DEBUG1 ("l2cu_dequeue_ccb  CID: 0x%04x", p_ccb->local_cid);

    /* Find out which queue the channel is on
    */
    if (p_ccb->p_lcb != NULL)
        p_q = &p_ccb->p_lcb->ccb_queue;

    if ( (!p_ccb->in_use) || (p_q == NULL) || (p_q->p_first_ccb == NULL) )
    {
        L2CAP_TRACE_ERROR5 ("l2cu_dequeue_ccb  CID: 0x%04x ERROR in_use: %u  p_lcb: 0x%08x  p_q: 0x%08x  p_q->p_first_ccb: 0x%08x",
                            p_ccb->local_cid, p_ccb->in_use, p_ccb->p_lcb, p_q, p_q ? p_q->p_first_ccb : 0);
        return;
    }

#if (L2CAP_ROUND_ROBIN_CHANNEL_SERVICE == TRUE)
    /* Removing CCB from round robin service table of its LCB */
    if (p_ccb->p_lcb != NULL)
    {
        /* decrease number of channels in this priority group */
        p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].num_ccb--;

        /* if it was the last channel in the priority group */
        if (p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].num_ccb == 0 )
        {
            p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_first_ccb = NULL;
            p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_serve_ccb = NULL;
        }
        else
        {
            /* if it is the first channel of this group */
            if ( p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_first_ccb == p_ccb )
            {
                p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_first_ccb = p_ccb->p_next_ccb;
            }
            /* if it is the next serving channel of this group */
            if ( p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_serve_ccb == p_ccb )
            {
                /* simply, start serving from the first channel */
                p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_serve_ccb
                    = p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_first_ccb;
            }
        }
    }
#endif

    if (p_ccb == p_q->p_first_ccb)
    {
        /* We are removing the first in a queue */
        p_q->p_first_ccb = p_ccb->p_next_ccb;

        if (p_q->p_first_ccb)
            p_q->p_first_ccb->p_prev_ccb = NULL;
        else
            p_q->p_last_ccb = NULL;
    }
    else if (p_ccb == p_q->p_last_ccb)
    {
        /* We are removing the last in a queue */
        p_q->p_last_ccb = p_ccb->p_prev_ccb;
        p_q->p_last_ccb->p_next_ccb = NULL;
    }
    else
    {
        /* In the middle of a chain. */
        p_ccb->p_prev_ccb->p_next_ccb = p_ccb->p_next_ccb;
        p_ccb->p_next_ccb->p_prev_ccb = p_ccb->p_prev_ccb;
    }

    p_ccb->p_next_ccb = p_ccb->p_prev_ccb = NULL;
}

/******************************************************************************
**
** Function         l2cu_change_pri_ccb
**
** Description
**
** Returns          -
**
*******************************************************************************/
void l2cu_change_pri_ccb (tL2C_CCB *p_ccb, tL2CAP_CHNL_PRIORITY priority)
{
    if (p_ccb->ccb_priority != priority)
    {
        /* If CCB is not the only guy on the queue */
        if ( (p_ccb->p_next_ccb != NULL) || (p_ccb->p_prev_ccb != NULL) )
        {
            L2CAP_TRACE_DEBUG0 ("Update CCB list in logical link");

            /* Remove CCB from queue and re-queue it at new priority */
            l2cu_dequeue_ccb (p_ccb);

            p_ccb->ccb_priority = priority;
            l2cu_enqueue_ccb (p_ccb);
        }
#if (L2CAP_ROUND_ROBIN_CHANNEL_SERVICE == TRUE)
        else
        {
        	/* If CCB is the only guy on the queue, no need to re-enqueue */
            /* update only round robin service data */
            p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].num_ccb = 0;
            p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_first_ccb = NULL;
            p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_serve_ccb = NULL;

            p_ccb->ccb_priority = priority;

            p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_first_ccb = p_ccb;
            p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].p_serve_ccb = p_ccb;
            p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].quota = L2CAP_GET_PRIORITY_QUOTA(p_ccb->ccb_priority);
            p_ccb->p_lcb->rr_serv[p_ccb->ccb_priority].num_ccb = 1;
        }
#endif
    }
}

/*******************************************************************************
**
** Function         l2cu_start_post_bond_timer
**
** Description      This function starts the ACL Link inactivity timer after
**                  dedicated bonding
**                  This timer can be longer than the normal link inactivity
**                  timer for some platforms.
**
** Returns          BOOLEAN  - TRUE if idle timer started or disconnect initiated
**                             FALSE if there's one or more pending CCB's exist
**
*******************************************************************************/
BOOLEAN l2cu_start_post_bond_timer (UINT16 handle)
{
    UINT16    timeout;
    tL2C_LCB *p_lcb = l2cu_find_lcb_by_handle(handle);

    if (!p_lcb)
        return (TRUE);

    p_lcb->is_bonding = FALSE;

    /* Only start timer if no control blocks allocated */
    if (p_lcb->ccb_queue.p_first_ccb != NULL)
        return (FALSE);

    /* If no channels on the connection, start idle timeout */
    if ( (p_lcb->link_state == LST_CONNECTED) || (p_lcb->link_state == LST_CONNECTING) || (p_lcb->link_state == LST_DISCONNECTING) )
    {
        if (p_lcb->idle_timeout == 0)
        {
            if (btsnd_hcic_disconnect (p_lcb->handle, HCI_ERR_PEER_USER))
            {
                p_lcb->link_state = LST_DISCONNECTING;
                timeout = L2CAP_LINK_DISCONNECT_TOUT;
            }
            else
                timeout = BT_1SEC_TIMEOUT;
        }
        else
        {
            timeout = L2CAP_BONDING_TIMEOUT;
        }

        if (timeout != 0xFFFF)
            btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, timeout);

        return (TRUE);
    }

    return (FALSE);
}

/*******************************************************************************
**
** Function         l2cu_find_ccb_by_remote_cid
**
** Description      Look through all active CCBs on a link for a match based
**                  on the remote CID.
**
** Returns          pointer to matched CCB, or NULL if no match
**
*******************************************************************************/
tL2C_CCB *l2cu_find_ccb_by_remote_cid (tL2C_LCB *p_lcb, UINT16 remote_cid)
{
    tL2C_CCB    *p_ccb;

    /* If LCB is NULL, look through all active links */
    if (!p_lcb)
    {
        return NULL;
    }
    else
    {
        for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_ccb->p_next_ccb)
            if ((p_ccb->in_use) && (p_ccb->remote_cid == remote_cid))
                return (p_ccb);
    }

    /* If here, no match found */
    return (NULL);
}

/*******************************************************************************
**
** Function         l2cu_disconnect_chnl
**
** Description      Disconnect a channel. Typically, this is due to either
**                  receiving a bad configuration,  bad packet or max_retries expiring.
**
*******************************************************************************/
void l2cu_disconnect_chnl (tL2C_CCB *p_ccb)
{
    UINT16      local_cid = p_ccb->local_cid;

    if (local_cid >= L2CAP_BASE_APPL_CID)
    {
        tL2CA_DISCONNECT_IND_CB   *p_disc_cb = p_ccb->p_rcb->api.pL2CA_DisconnectInd_Cb;

        L2CAP_TRACE_WARNING1 ("L2CAP - disconnect_chnl CID: 0x%04x", local_cid);

        l2cu_send_peer_disc_req (p_ccb);

        l2cu_release_ccb (p_ccb);

        (*p_disc_cb)(local_cid, FALSE);
    }
    else
    {
        /* failure on the AMP channel, probably need to disconnect ACL */
        L2CAP_TRACE_ERROR1 ("L2CAP - disconnect_chnl CID: 0x%04x Ignored", local_cid);
    }
}

/*******************************************************************************
**
** Function         l2cu_get_num_hi_priority
**
** Description      Gets the number of high priority channels.
**
** Returns
**
*******************************************************************************/
UINT8 l2cu_get_num_hi_priority (void)
{
    UINT8       no_hi = 0;
    int         xx;
    tL2C_LCB    *p_lcb = &l2cb.lcb_pool[0];

    for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p_lcb++)
    {
        if ((p_lcb->in_use) && (p_lcb->acl_priority == L2CAP_PRIORITY_HIGH))
        {
            no_hi++;
        }
    }
    return no_hi;
}

/*******************************************************************************
**
** Function         l2cu_set_acl_priority
**
** Description      Sets the transmission priority for a channel.
**                  (For initial implementation only two values are valid.
**                  L2CAP_PRIORITY_NORMAL and L2CAP_PRIORITY_HIGH).
**
** Returns          TRUE if a valid channel, else FALSE
**
*******************************************************************************/

BOOLEAN l2cu_set_acl_priority (BD_ADDR bd_addr, UINT8 priority, BOOLEAN reset_after_rs)
{
    tL2C_LCB            *p_lcb;
    UINT8               *pp;
    UINT8                command[HCI_BRCM_ACL_PRIORITY_PARAM_SIZE];
    UINT8                vs_param;

    APPL_TRACE_EVENT1("SET ACL PRIORITY %d", priority);

    /* Find the link control block for the acl channel */
    if ((p_lcb = l2cu_find_lcb_by_bd_addr(bd_addr)) == NULL)
    {
        L2CAP_TRACE_WARNING0 ("L2CAP - no LCB for L2CA_SetAclPriority");
        return (FALSE);
    }

    if (BTM_IS_BRCM_CONTROLLER())
    {
        /* Called from above L2CAP through API; send VSC if changed */
        if ((!reset_after_rs && (priority != p_lcb->acl_priority)) ||
              /* Called because of a master/slave role switch; if high resend VSC */
            ( reset_after_rs && p_lcb->acl_priority == L2CAP_PRIORITY_HIGH))
        {
            pp = command;

            vs_param = (priority == L2CAP_PRIORITY_HIGH) ? HCI_BRCM_ACL_PRIORITY_HIGH : HCI_BRCM_ACL_PRIORITY_LOW;

            UINT16_TO_STREAM (pp, p_lcb->handle);
            UINT8_TO_STREAM  (pp, vs_param);

            BTM_VendorSpecificCommand (HCI_BRCM_SET_ACL_PRIORITY, HCI_BRCM_ACL_PRIORITY_PARAM_SIZE, command, NULL);

            /* Adjust lmp buffer allocation for this channel if priority changed */
            if (p_lcb->acl_priority != priority)
            {
                p_lcb->acl_priority = priority;
                l2c_link_adjust_allocation();
            }
        }
    }
    return(TRUE);
}

#if (L2CAP_ENHANCED_FEATURES != 0)

/*******************************************************************************
**
** Function         l2cu_send_feature_req
**
** Description      Called at connection establishment by the originator
**                  of the connection to send an L2CAP Echo request message
**                  to the peer to determine if he supports Widcomm proprietary
**                  features.
**
** Returns          void
**
*******************************************************************************/
void l2cu_send_feature_req (tL2C_CCB *p_ccb)
{
    UINT8     saved_id;
    UINT8     buff[100], *p = buff;

    UINT8_TO_STREAM (p, 'R');
    UINT8_TO_STREAM (p, 'Q');

    UINT8_TO_STREAM (p, 'r');
    UINT8_TO_STREAM (p, 'q');

    /* save current ID to be restored after feature request */
    saved_id = p_ccb->p_lcb->id;

    /* Set appropriate ID */
    p_ccb->p_lcb->id               = L2CAP_FEATURE_REQ_ID - 1;

    l2cu_send_peer_echo_req (p_ccb->p_lcb, buff, (UINT16)(p - buff));

    /* packet has been built so we can restore the control block id */
    p_ccb->p_lcb->id = saved_id;
}

/*******************************************************************************
**
** Function         l2cu_check_feature_req
**
** Description      Called when an echo request is received to check if the
**                  other side is doing a proprietary feature request. If so,
**                  extract the values and reply with a features response.
**
** Returns          void
**
*******************************************************************************/
BOOLEAN l2cu_check_feature_req (tL2C_LCB *p_lcb, UINT8 id, UINT8 *p_data, UINT16 data_len)
{
    UINT8   buff[100];
    UINT8   *p_out           = buff;
    UINT8   *p_end           = p_data + data_len - 2;
    UINT8   pe_type, pe_len;

    if ((data_len <= 4)
     || (p_data[0] != 'R')
     || (p_data[1] != 'Q')
     || (p_data[data_len - 2] != 'r')
     || (p_data[data_len - 1] != 'q')
     || (id != L2CAP_FEATURE_REQ_ID))
        return (FALSE);

    /* Skip leading frame characters */
    p_data += 2;

    UINT8_TO_STREAM (p_out, 'R');
    UINT8_TO_STREAM (p_out, 'S');

    while (p_data < p_end)
    {
        pe_type  = *p_data++;
        pe_len   = *p_data++;

        switch (pe_type)
        {
        default:
            p_data += pe_len;
            break;
        }
    }

    /* Sanity check - we should not overrun the input */
    if (p_data != p_end)
    {
        L2CAP_TRACE_ERROR0 ("L2CAP - badly formatted feature req");
        return (FALSE);
    }

    UINT8_TO_STREAM (p_out, 'r');
    UINT8_TO_STREAM (p_out, 's');

    l2cu_send_peer_echo_rsp (p_lcb, L2CAP_FEATURE_RSP_ID, buff, (UINT16)(p_out - buff));

    return (TRUE);
}

/*******************************************************************************
**
** Function         l2cu_check_feature_rsp
**
** Description      Called when an echo response is received to check if the
**                  other side is suports proprietary feature(s). If so,
**                  extract the values.
**
** Returns          void
**
*******************************************************************************/
void l2cu_check_feature_rsp (tL2C_LCB *p_lcb, UINT8 id, UINT8 *p_data, UINT16 data_len)
{
    UINT8       *p_end = p_data + data_len - 2;

     if ((data_len <= 4)
       || (p_data[0] != 'R')
       || (p_data[1] != 'S')
       || (p_data[data_len - 2] != 'r')
       || (p_data[data_len - 1] != 's')
       || (id != L2CAP_FEATURE_RSP_ID))
    {
        return;
    }

    /* Skip leading frame characters */
    p_data += 2;

    while (p_data < p_end)
    {
        UINT8   pe_id  = *p_data++;
        UINT8   pe_len = *p_data++;

        switch (pe_id)
        {
        default:
            p_data += pe_len;
            break;
        }
    }

    /* Sanity check - we should not overrun the input */
    if (p_data != p_end)
    {
        L2CAP_TRACE_ERROR0 ("L2CAP - badly formatted feature rsp");
    }
}
#endif /* L2CAP_ENHANCED_FEATURES != 0 */

#if (L2CAP_NON_FLUSHABLE_PB_INCLUDED == TRUE)

/******************************************************************************
**
** Function         l2cu_set_non_flushable_pbf
**
** Description      set L2CAP_PKT_START_NON_FLUSHABLE if controller supoorts
**
** Returns          void
**
*******************************************************************************/
void l2cu_set_non_flushable_pbf (BOOLEAN is_supported)
{
    if (is_supported)
        l2cb.non_flushable_pbf = (L2CAP_PKT_START_NON_FLUSHABLE << L2CAP_PKT_TYPE_SHIFT);
    else
        l2cb.non_flushable_pbf = (L2CAP_PKT_START << L2CAP_PKT_TYPE_SHIFT);
}
#endif

/*******************************************************************************
**
** Function         l2cu_resubmit_pending_sec_req
**
** Description      This function is called when required security procedures
**                  are completed and any pending requests can be re-submitted.
**
** Returns          void
**
*******************************************************************************/
void l2cu_resubmit_pending_sec_req (BD_ADDR p_bda)
{
    tL2C_LCB        *p_lcb;
    tL2C_CCB        *p_ccb;
    tL2C_CCB        *p_next_ccb;
    int             xx;

    L2CAP_TRACE_DEBUG1 ("l2cu_resubmit_pending_sec_req  p_bda: 0x%08x", p_bda);

    /* If we are called with a BDA, only resubmit for that BDA */
    if (p_bda)
    {
        p_lcb = l2cu_find_lcb_by_bd_addr (p_bda);

        /* If we don't have one, this is an error */
        if (p_lcb)
        {
            /* For all channels, send the event through their FSMs */
            for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_next_ccb)
            {
                p_next_ccb = p_ccb->p_next_ccb;
                l2c_csm_execute (p_ccb, L2CEVT_SEC_RE_SEND_CMD, NULL);
            }
        }
        else
        {
            L2CAP_TRACE_WARNING0 ("l2cu_resubmit_pending_sec_req - unknown BD_ADDR");
        }
    }
    else
    {
        /* No BDA pasesed in, so check all links */
        for (xx = 0, p_lcb = &l2cb.lcb_pool[0]; xx < MAX_L2CAP_LINKS; xx++, p_lcb++)
        {
            if (p_lcb->in_use)
            {
                /* For all channels, send the event through their FSMs */
                for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_next_ccb)
                {
                    p_next_ccb = p_ccb->p_next_ccb;
                    l2c_csm_execute (p_ccb, L2CEVT_SEC_RE_SEND_CMD, NULL);
                }
            }
        }
    }
}

#if L2CAP_CONFORMANCE_TESTING == TRUE

/*******************************************************************************
**
** Function         l2cu_set_info_rsp_mask
**
** Description      This function allows the script wrapper to change the
**                  info resp mask for conformance testing.
**
** Returns          pointer to CCB, or NULL if none
**
*******************************************************************************/
void l2cu_set_info_rsp_mask (UINT32 mask)
{
    l2cb.test_info_resp = mask;
}
#endif  /* L2CAP_CONFORMANCE_TESTING */

/*******************************************************************************
**
** Function         l2cu_adjust_out_mps
**
** Description      Sets our MPS based on current controller capabilities
**
** Returns          void
**
*******************************************************************************/
void l2cu_adjust_out_mps (tL2C_CCB *p_ccb)
{
    UINT16 packet_size;

    /* on the tx side MTU is selected based on packet size of the controller */
    packet_size = btm_get_max_packet_size (p_ccb->p_lcb->remote_bd_addr);

    if (packet_size <= (L2CAP_PKT_OVERHEAD + L2CAP_FCR_OVERHEAD + L2CAP_SDU_LEN_OVERHEAD + L2CAP_FCS_LEN))
    {
        /* something is very wrong */
        L2CAP_TRACE_ERROR2 ("l2cu_adjust_out_mps bad packet size: %u  will use MPS: %u", packet_size, p_ccb->peer_cfg.fcr.mps);
        p_ccb->tx_mps = p_ccb->peer_cfg.fcr.mps;
    }
    else
    {
        packet_size -= (L2CAP_PKT_OVERHEAD + L2CAP_FCR_OVERHEAD + L2CAP_SDU_LEN_OVERHEAD + L2CAP_FCS_LEN);

        /* We try to negotiate MTU that each packet can be split into whole
        number of max packets.  For example if link is 1.2 max packet size is 339 bytes.
        At first calculate how many whole packets it is.  MAX L2CAP is 1691 + 4 overhead.
        1695, that will be 5 Dh5 packets.  Now maximum L2CAP packet is
        5 * 339 = 1695. Minus 4 bytes L2CAP header 1691.

        For EDR 2.0 packet size is 1027.  So we better send RFCOMM packet as 1 3DH5 packet
        1 * 1027 = 1027.  Minus 4 bytes L2CAP header 1023.  */
        if (p_ccb->peer_cfg.fcr.mps >= packet_size)
            p_ccb->tx_mps = p_ccb->peer_cfg.fcr.mps / packet_size * packet_size;
        else
            p_ccb->tx_mps = p_ccb->peer_cfg.fcr.mps;

        L2CAP_TRACE_DEBUG3 ("l2cu_adjust_out_mps use %d   Based on peer_cfg.fcr.mps: %u  packet_size: %u",
                            p_ccb->tx_mps, p_ccb->peer_cfg.fcr.mps, packet_size);
    }
}

/*******************************************************************************
**
** Function         l2cu_initialize_fixed_ccb
**
** Description      Initialize a fixed channel's CCB
**
** Returns          TRUE or FALSE
**
*******************************************************************************/
BOOLEAN l2cu_initialize_fixed_ccb (tL2C_LCB *p_lcb, UINT16 fixed_cid, tL2CAP_FCR_OPTS *p_fcr)
{
#if (L2CAP_NUM_FIXED_CHNLS > 0)
    tL2C_CCB    *p_ccb;

    /* If we already have a CCB, then simply return */
    if (p_lcb->p_fixed_ccbs[fixed_cid - L2CAP_FIRST_FIXED_CHNL] != NULL)
        return (TRUE);

    if ((p_ccb = l2cu_allocate_ccb (NULL, 0)) == NULL)
        return (FALSE);

    /* Set CID for the connection */
    p_ccb->local_cid  = fixed_cid;
    p_ccb->remote_cid = fixed_cid;

    GKI_init_q (&p_ccb->xmit_hold_q);

    p_ccb->is_flushable = FALSE;

    p_ccb->timer_entry.param  = (TIMER_PARAM_TYPE)p_ccb;


    if (p_fcr)
    {
        /* Set the FCR parameters. For now, we will use default pools */
        p_ccb->our_cfg.fcr = p_ccb->peer_cfg.fcr = *p_fcr;

        p_ccb->ertm_info.fcr_rx_pool_id  = HCI_ACL_POOL_ID;
        p_ccb->ertm_info.fcr_tx_pool_id  = HCI_ACL_POOL_ID;
        p_ccb->ertm_info.user_rx_pool_id = HCI_ACL_POOL_ID;
        p_ccb->ertm_info.user_tx_pool_id = HCI_ACL_POOL_ID;

        p_ccb->fcrb.max_held_acks = p_fcr->tx_win_sz / 3;
    }

    /* Link ccb to lcb and lcb to ccb */
    p_lcb->p_fixed_ccbs[fixed_cid - L2CAP_FIRST_FIXED_CHNL] = p_ccb;
    p_ccb->p_lcb = p_lcb;

    /* There is no configuration, so if the link is up, the channel is up */
    if (p_lcb->link_state == LST_CONNECTED)
        p_ccb->chnl_state = CST_OPEN;

    /* Set the default idle timeout value to use */
    p_ccb->fixed_chnl_idle_tout = l2cb.fixed_reg[fixed_cid - L2CAP_FIRST_FIXED_CHNL].default_idle_tout;
#endif
    return (TRUE);
}

/*******************************************************************************
**
** Function         l2cu_no_dynamic_ccbs
**
** Description      Handles the case when there are no more dynamic CCBs. If there
**                  are any fixed CCBs, start the longest of the fixed CCB timeouts,
**                  otherwise start the default link idle timeout or disconnect.
**
** Returns          void
**
*******************************************************************************/
void l2cu_no_dynamic_ccbs (tL2C_LCB *p_lcb)
{
    tBTM_STATUS     rc;
    UINT16          timeout = p_lcb->idle_timeout;

#if (L2CAP_NUM_FIXED_CHNLS > 0)
    int         xx;

    for (xx = 0; xx < L2CAP_NUM_FIXED_CHNLS; xx++)
    {
        if ( (p_lcb->p_fixed_ccbs[xx] != NULL) && (p_lcb->p_fixed_ccbs[xx]->fixed_chnl_idle_tout > timeout) )
            timeout = p_lcb->p_fixed_ccbs[xx]->fixed_chnl_idle_tout;
    }
#endif

    /* If the link is pairing, do not mess with the timeouts */
    if (p_lcb->is_bonding)
        return;

    if (timeout == 0)
    {
        L2CAP_TRACE_DEBUG0 ("l2cu_no_dynamic_ccbs() IDLE timer 0, disconnecting link");

        rc = btm_sec_disconnect (p_lcb->handle, HCI_ERR_PEER_USER);
        if (rc == BTM_CMD_STARTED)
        {
            p_lcb->link_state = LST_DISCONNECTING;
            timeout = L2CAP_LINK_DISCONNECT_TOUT;
        }
        else if (rc == BTM_SUCCESS)
        {
            /* BTM SEC will make sure that link is release (probably after pairing is done) */
            p_lcb->link_state = LST_DISCONNECTING;
            timeout = 0xFFFF;
        }
        else if ( (p_lcb->is_bonding)
            &&   (btsnd_hcic_disconnect (p_lcb->handle, HCI_ERR_PEER_USER)) )
        {
            p_lcb->link_state = LST_DISCONNECTING;
            timeout = L2CAP_LINK_DISCONNECT_TOUT;
        }
        else
        {
            /* probably no buffer to send disconnect */
            timeout = BT_1SEC_TIMEOUT;
        }
    }

    if (timeout != 0xFFFF)
    {
        L2CAP_TRACE_DEBUG1 ("l2cu_no_dynamic_ccbs() starting IDLE timeout: %d", timeout);
        btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, timeout);
    }
    else
    {
        btu_stop_timer(&p_lcb->timer_entry);
    }
}

#if (L2CAP_NUM_FIXED_CHNLS > 0)

/*******************************************************************************
**
** Function         l2cu_process_fixed_chnl_resp
**
** Description      handle a fixed channel response (or lack thereof)
**                  if the link failed, or a fixed channel response was
**                  not received, the bitfield is all zeros.
**
*******************************************************************************/
void l2cu_process_fixed_chnl_resp (tL2C_LCB *p_lcb)
{
    int     xx;
#if BLE_INCLUDED == TRUE
    UINT16  reason = (p_lcb->is_ble_link ) ? 1 : 0;
#else
    UINT16 reason =0;
#endif

    /* Tell all registered fixed channels about the connection */
    for (xx = 0; xx < L2CAP_NUM_FIXED_CHNLS; xx++)
    {
        if (l2cb.fixed_reg[xx].pL2CA_FixedConn_Cb != NULL)
        {
            if (p_lcb->peer_chnl_mask[0] & (1 << (xx + L2CAP_FIRST_FIXED_CHNL)))
            {
                if (p_lcb->p_fixed_ccbs[xx])
                    p_lcb->p_fixed_ccbs[xx]->chnl_state = CST_OPEN;

                (*l2cb.fixed_reg[xx].pL2CA_FixedConn_Cb)(p_lcb->remote_bd_addr, TRUE, reason);
            }
            else if (p_lcb->p_fixed_ccbs[xx])
            {
                (*l2cb.fixed_reg[xx].pL2CA_FixedConn_Cb)(p_lcb->remote_bd_addr, FALSE, p_lcb->disc_reason);
                l2cu_release_ccb (p_lcb->p_fixed_ccbs[xx]);
                p_lcb->p_fixed_ccbs[xx] = NULL;
            }
        }
    }
}
#endif

#if (BLE_INCLUDED == TRUE)

/*******************************************************************************
**
** Function         l2cu_send_peer_ble_par_req
**
** Description      Build and send a BLE parameter update request message
**                  to the peer.
**
** Returns          void
**
*******************************************************************************/
void l2cu_send_peer_ble_par_req (tL2C_LCB *p_lcb, UINT16 min_int, UINT16 max_int, UINT16 latency, UINT16 timeout)
{
    BT_HDR  *p_buf;
    UINT8   *p;

    /* Create an identifier for this packet */
    p_lcb->id++;
    l2cu_adj_id (p_lcb, L2CAP_ADJ_ID);

    if ((p_buf = l2cu_build_header (p_lcb, L2CAP_CMD_BLE_UPD_REQ_LEN, L2CAP_CMD_BLE_UPDATE_REQ, p_lcb->id)) == NULL )
    {
        L2CAP_TRACE_WARNING0 ("l2cu_send_peer_ble_par_req - no buffer");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET + HCI_DATA_PREAMBLE_SIZE +
                               L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    UINT16_TO_STREAM (p, min_int);
    UINT16_TO_STREAM (p, max_int);
    UINT16_TO_STREAM (p, latency);
    UINT16_TO_STREAM (p, timeout);

    l2c_link_check_send_pkts (p_lcb, NULL, p_buf);
}

/*******************************************************************************
**
** Function         l2cu_send_peer_ble_par_rsp
**
** Description      Build and send a BLE parameter update response message
**                  to the peer.
**
** Returns          void
**
*******************************************************************************/
void l2cu_send_peer_ble_par_rsp (tL2C_LCB *p_lcb, UINT16 reason, UINT8 rem_id)
{
    BT_HDR  *p_buf;
    UINT8   *p;

    if ((p_buf = l2cu_build_header (p_lcb, L2CAP_CMD_BLE_UPD_RSP_LEN, L2CAP_CMD_BLE_UPDATE_RSP, rem_id)) == NULL )
    {
        L2CAP_TRACE_WARNING0 ("l2cu_send_peer_ble_par_rsp - no buffer");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET + HCI_DATA_PREAMBLE_SIZE +
                               L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    UINT16_TO_STREAM (p, reason);

    l2c_link_check_send_pkts (p_lcb, NULL, p_buf);
}

#endif /* BLE_INCLUDED == TRUE */


/*******************************************************************************
** Functions used by both Full and Light Stack
********************************************************************************/

/******************************************************************************
**
** Function         l2cu_get_next_channel_in_rr
**
** Description      get the next channel to send on a link. It also adjusts the
**                  CCB queue to do a basic priority and round-robin scheduling.
**
** Returns          pointer to CCB or NULL
**
*******************************************************************************/
static tL2C_CCB *l2cu_get_next_channel_in_rr(tL2C_LCB *p_lcb)
{
    tL2C_CCB    *p_serve_ccb = NULL;
    tL2C_CCB    *p_ccb;

    int i, j;

    /* scan all of priority until finding a channel to serve */
    for ( i = 0; (i < L2CAP_NUM_CHNL_PRIORITY)&&(!p_serve_ccb); i++ )
    {
        /* scan all channel within serving priority group until finding a channel to serve */
        for ( j = 0; (j < p_lcb->rr_serv[p_lcb->rr_pri].num_ccb)&&(!p_serve_ccb); j++)
        {
            /* scaning from next serving channel */
            p_ccb = p_lcb->rr_serv[p_lcb->rr_pri].p_serve_ccb;

            if (!p_ccb)
            {
                L2CAP_TRACE_ERROR1("p_serve_ccb is NULL, rr_pri=%d", p_lcb->rr_pri);
                return NULL;
            }

            L2CAP_TRACE_DEBUG3("RR scan pri=%d, lcid=0x%04x, q_cout=%d",
                                p_ccb->ccb_priority, p_ccb->local_cid, p_ccb->xmit_hold_q.count );

            /* store the next serving channel */
            /* this channel is the last channel of its priority group */
            if (( p_ccb->p_next_ccb == NULL )
              ||( p_ccb->p_next_ccb->ccb_priority != p_ccb->ccb_priority ))
            {
                /* next serving channel is set to the first channel in the group */
                p_lcb->rr_serv[p_lcb->rr_pri].p_serve_ccb = p_lcb->rr_serv[p_lcb->rr_pri].p_first_ccb;
            }
            else
            {
                /* next serving channel is set to the next channel in the group */
                p_lcb->rr_serv[p_lcb->rr_pri].p_serve_ccb = p_ccb->p_next_ccb;
            }

            if (p_ccb->chnl_state != CST_OPEN)
                continue;

            /* eL2CAP option in use */
            if (p_ccb->peer_cfg.fcr.mode != L2CAP_FCR_BASIC_MODE)
            {
                if (p_ccb->fcrb.wait_ack || p_ccb->fcrb.remote_busy)
                    continue;

                if ( p_ccb->fcrb.retrans_q.count == 0 )
                {
                    if ( p_ccb->xmit_hold_q.count == 0 )
                        continue;

                    /* If using the common pool, should be at least 10% free. */
                    if ( (p_ccb->ertm_info.fcr_tx_pool_id == HCI_ACL_POOL_ID) && (GKI_poolutilization (HCI_ACL_POOL_ID) > 90) )
                        continue;

                    /* If in eRTM mode, check for window closure */
                    if ( (p_ccb->peer_cfg.fcr.mode == L2CAP_FCR_ERTM_MODE) && (l2c_fcr_is_flow_controlled (p_ccb)) )
                        continue;
                }
            }
            else
            {
                if (p_ccb->xmit_hold_q.count == 0)
                    continue;
            }

            /* found a channel to serve */
            p_serve_ccb = p_ccb;
            /* decrease quota of its priority group */
            p_lcb->rr_serv[p_lcb->rr_pri].quota--;
        }

        /* if there is no more quota of the priority group or no channel to have data to send */
        if ((p_lcb->rr_serv[p_lcb->rr_pri].quota == 0)||(!p_serve_ccb))
        {
            /* serve next priority group */
            p_lcb->rr_pri = (p_lcb->rr_pri + 1) % L2CAP_NUM_CHNL_PRIORITY;
            /* initialize its quota */
            p_lcb->rr_serv[p_lcb->rr_pri].quota = L2CAP_GET_PRIORITY_QUOTA(p_lcb->rr_pri);
        }
    }

    if (p_serve_ccb)
    {
        L2CAP_TRACE_DEBUG3("RR service pri=%d, quota=%d, lcid=0x%04x",
                            p_serve_ccb->ccb_priority,
                            p_lcb->rr_serv[p_serve_ccb->ccb_priority].quota,
                            p_serve_ccb->local_cid );
    }

    return p_serve_ccb;
}

#if (L2CAP_ROUND_ROBIN_CHANNEL_SERVICE != TRUE)

/******************************************************************************
**
** Function         l2cu_get_next_channel
**
** Description      get the next channel to send on a link bassed on priority
**                  scheduling.
**
** Returns          pointer to CCB or NULL
**
*******************************************************************************/
static tL2C_CCB *l2cu_get_next_channel(tL2C_LCB *p_lcb)
{
    tL2C_CCB    *p_ccb;

    /* Get the first CCB with data to send.
    */
    for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_ccb->p_next_ccb)
    {
        if (p_ccb->chnl_state != CST_OPEN)
            continue;

        if (p_ccb->fcrb.wait_ack || p_ccb->fcrb.remote_busy)
            continue;

        if (p_ccb->fcrb.retrans_q.count != 0)
            return p_ccb;

        if (p_ccb->xmit_hold_q.count == 0)
            continue;

        /* If using the common pool, should be at least 10% free. */
        if ( (p_ccb->ertm_info.fcr_tx_pool_id == HCI_ACL_POOL_ID) && (GKI_poolutilization (HCI_ACL_POOL_ID) > 90) )
            continue;

        /* If in eRTM mode, check for window closure */
        if ( (p_ccb->peer_cfg.fcr.mode == L2CAP_FCR_ERTM_MODE) && (l2c_fcr_is_flow_controlled (p_ccb)) )
            continue;

        /* If here, we found someone */
        return p_ccb;
    }

    return NULL;
}
#endif /* (L2CAP_ROUND_ROBIN_CHANNEL_SERVICE == TRUE) */

/******************************************************************************
**
** Function         l2cu_get_next_buffer_to_send
**
** Description      get the next buffer to send on a link. It also adjusts the
**                  CCB queue to do a basic priority and round-robin scheduling.
**
** Returns          pointer to buffer or NULL
**
*******************************************************************************/
BT_HDR *l2cu_get_next_buffer_to_send (tL2C_LCB *p_lcb)
{
    tL2C_CCB    *p_ccb;
    BT_HDR      *p_buf;

    /* Highest priority are fixed channels */
#if (L2CAP_NUM_FIXED_CHNLS > 0)
    int         xx;

    for (xx = 0; xx < L2CAP_NUM_FIXED_CHNLS; xx++)
    {
        if ((p_ccb = p_lcb->p_fixed_ccbs[xx]) == NULL)
            continue;

        /* eL2CAP option in use */
        if (p_ccb->peer_cfg.fcr.mode != L2CAP_FCR_BASIC_MODE)
        {
            if (p_ccb->fcrb.wait_ack || p_ccb->fcrb.remote_busy)
                continue;

            /* No more checks needed if sending from the reatransmit queue */
            if (p_ccb->fcrb.retrans_q.count == 0)
            {
                if (p_ccb->xmit_hold_q.count == 0)
                    continue;

                /* If using the common pool, should be at least 10% free. */
                if ( (p_ccb->ertm_info.fcr_tx_pool_id == HCI_ACL_POOL_ID) && (GKI_poolutilization (HCI_ACL_POOL_ID) > 90) )
                    continue;

                /* If in eRTM mode, check for window closure */
                if ( (p_ccb->peer_cfg.fcr.mode == L2CAP_FCR_ERTM_MODE) && (l2c_fcr_is_flow_controlled (p_ccb)) )
                    continue;
            }

            if ((p_buf = l2c_fcr_get_next_xmit_sdu_seg(p_ccb, 0)) != NULL)
            {
                l2cu_set_acl_hci_header (p_buf, p_ccb);
                return (p_buf);
            }
        }
        else
        {
            if (p_ccb->xmit_hold_q.count != 0)
            {
                p_buf = (BT_HDR *)GKI_dequeue (&p_ccb->xmit_hold_q);
                l2cu_set_acl_hci_header (p_buf, p_ccb);
                return (p_buf);
            }
        }
    }
#endif

#if (L2CAP_ROUND_ROBIN_CHANNEL_SERVICE == TRUE)
    /* get next serving channel in round-robin */
    p_ccb  = l2cu_get_next_channel_in_rr( p_lcb );
#else
    p_ccb  = l2cu_get_next_channel( p_lcb );
#endif

    /* Return if no buffer */
    if (p_ccb == NULL)
        return (NULL);

    if (p_ccb->peer_cfg.fcr.mode != L2CAP_FCR_BASIC_MODE)
    {
        if ((p_buf = l2c_fcr_get_next_xmit_sdu_seg(p_ccb, 0)) == NULL)
            return (NULL);
    }
    else
    {
        p_buf = (BT_HDR *)GKI_dequeue (&p_ccb->xmit_hold_q);
    }

#ifndef REVOLUTION
    if ( p_ccb->p_rcb && p_ccb->p_rcb->api.pL2CA_TxComplete_Cb && (p_ccb->peer_cfg.fcr.mode != L2CAP_FCR_ERTM_MODE) )
        (*p_ccb->p_rcb->api.pL2CA_TxComplete_Cb)(p_ccb->local_cid, 1);
#endif


    l2cu_check_channel_congestion (p_ccb);

    l2cu_set_acl_hci_header (p_buf, p_ccb);

    return (p_buf);
}

/******************************************************************************
**
** Function         l2cu_set_acl_hci_header
**
** Description      Set HCI handle for ACL packet
**
** Returns          None
**
*******************************************************************************/
void l2cu_set_acl_hci_header (BT_HDR *p_buf, tL2C_CCB *p_ccb)
{
    UINT8       *p;

    /* Set the pointer to the beginning of the data minus 4 bytes for the packet header */
    p = (UINT8 *)(p_buf + 1) + p_buf->offset - HCI_DATA_PREAMBLE_SIZE;

#if (L2CAP_NON_FLUSHABLE_PB_INCLUDED == TRUE)
    if ( (((p_buf->layer_specific & L2CAP_FLUSHABLE_MASK) == L2CAP_FLUSHABLE_CH_BASED) && (p_ccb->is_flushable))
            || ((p_buf->layer_specific & L2CAP_FLUSHABLE_MASK) == L2CAP_FLUSHABLE_PKT) )
    {
        UINT16_TO_STREAM (p, p_ccb->p_lcb->handle | (L2CAP_PKT_START << L2CAP_PKT_TYPE_SHIFT));
    }
    else
    {
        UINT16_TO_STREAM (p, p_ccb->p_lcb->handle | l2cb.non_flushable_pbf);
    }
#else
    UINT16_TO_STREAM (p, p_ccb->p_lcb->handle | (L2CAP_PKT_START << L2CAP_PKT_TYPE_SHIFT));
#endif
#if (BLE_INCLUDED == TRUE)
    if (p_ccb->p_lcb->is_ble_link)
    {
        /* The HCI transport will segment the buffers. */
        if (p_buf->len > btu_cb.hcit_ble_acl_data_size)
        {
            UINT16_TO_STREAM (p, btu_cb.hcit_ble_acl_data_size);
        }
        else
        {
            UINT16_TO_STREAM (p, p_buf->len);
        }
    } /* (BLE_INCLUDED == TRUE) */
    else
#endif
    {

        /* The HCI transport will segment the buffers. */
        if (p_buf->len > btu_cb.hcit_acl_data_size)
        {
            UINT16_TO_STREAM (p, btu_cb.hcit_acl_data_size);
        }
        else
        {
            UINT16_TO_STREAM (p, p_buf->len);
        }
    }
    p_buf->offset -= HCI_DATA_PREAMBLE_SIZE;
    p_buf->len    += HCI_DATA_PREAMBLE_SIZE;
}

/******************************************************************************
**
** Function         l2cu_check_channel_congestion
**
** Description      check if any change in congestion status
**
** Returns          None
**
*******************************************************************************/
void l2cu_check_channel_congestion (tL2C_CCB *p_ccb)
{
    UINT16 q_count = p_ccb->xmit_hold_q.count;

#if (L2CAP_UCD_INCLUDED == TRUE)
    if ( p_ccb->local_cid == L2CAP_CONNECTIONLESS_CID )
    {
        q_count += p_ccb->p_lcb->ucd_out_sec_pending_q.count;
    }
#endif

    /* If the CCB queue limit is subject to a quota, check for congestion */

    /* if this channel has outgoing traffic */
    if ((p_ccb->p_rcb)&&(p_ccb->buff_quota != 0))
    {
        /* If this channel was congested */
        if ( p_ccb->cong_sent )
        {
            /* If the channel is not congested now, tell the app */
            if (q_count <= (p_ccb->buff_quota / 2))
            {
                p_ccb->cong_sent = FALSE;
                if (p_ccb->p_rcb->api.pL2CA_CongestionStatus_Cb)
                {
                    L2CAP_TRACE_DEBUG3 ("L2CAP - Calling CongestionStatus_Cb (FALSE), CID: 0x%04x  xmit_hold_q.count: %u  buff_quota: %u",
                                      p_ccb->local_cid, q_count, p_ccb->buff_quota);

                    /* Prevent recursive calling */
                    l2cb.is_cong_cback_context = TRUE;
                    (*p_ccb->p_rcb->api.pL2CA_CongestionStatus_Cb)(p_ccb->local_cid, FALSE);
                    l2cb.is_cong_cback_context = FALSE;
                }
#if (L2CAP_UCD_INCLUDED == TRUE)
                else if ( p_ccb->local_cid == L2CAP_CONNECTIONLESS_CID )
                {
                    if ( p_ccb->p_rcb->ucd.cb_info.pL2CA_UCD_Congestion_Status_Cb )
                    {
                        L2CAP_TRACE_DEBUG3 ("L2CAP - Calling UCD CongestionStatus_Cb (FALSE), SecPendingQ:%u,XmitQ:%u,Quota:%u",
                                             p_ccb->p_lcb->ucd_out_sec_pending_q.count,
                                             p_ccb->xmit_hold_q.count, p_ccb->buff_quota);
                        p_ccb->p_rcb->ucd.cb_info.pL2CA_UCD_Congestion_Status_Cb( p_ccb->p_lcb->remote_bd_addr, FALSE );
                    }
                }
#endif
            }
        }
        else
        {
            /* If this channel was not congested but it is congested now, tell the app */
            if (q_count > p_ccb->buff_quota)
            {
                p_ccb->cong_sent = TRUE;
                if (p_ccb->p_rcb->api.pL2CA_CongestionStatus_Cb)
                {
                    L2CAP_TRACE_DEBUG3 ("L2CAP - Calling CongestionStatus_Cb (TRUE),CID:0x%04x,XmitQ:%u,Quota:%u",
                        p_ccb->local_cid, q_count, p_ccb->buff_quota);

                    (*p_ccb->p_rcb->api.pL2CA_CongestionStatus_Cb)(p_ccb->local_cid, TRUE);
                }
#if (L2CAP_UCD_INCLUDED == TRUE)
                else if ( p_ccb->local_cid == L2CAP_CONNECTIONLESS_CID )
                {
                    if ( p_ccb->p_rcb->ucd.cb_info.pL2CA_UCD_Congestion_Status_Cb )
                    {
                        L2CAP_TRACE_DEBUG3 ("L2CAP - Calling UCD CongestionStatus_Cb (TRUE), SecPendingQ:%u,XmitQ:%u,Quota:%u",
                                             p_ccb->p_lcb->ucd_out_sec_pending_q.count,
                                             p_ccb->xmit_hold_q.count, p_ccb->buff_quota);
                        p_ccb->p_rcb->ucd.cb_info.pL2CA_UCD_Congestion_Status_Cb( p_ccb->p_lcb->remote_bd_addr, TRUE );
                    }
                }
#endif
            }
        }
    }
}
#endif
