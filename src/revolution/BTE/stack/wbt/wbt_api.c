/* Wii's DI record uses three 80-byte optional strings. */
#define SDP_MAX_ATTR_LEN 80

#include <string.h>

#include "bt_types.h"
#include "sdp_api.h"
#include "wbt_api.h"

BOOLEAN WBT_ExtCreateRecord(void) {
    tSDP_DI_GET_RECORD device_info;
    /* Preserve the original failure-path handle reset before returning. */
    volatile UINT32 handle = 0;
    UINT8 version[2];
    UINT16 browse_group = UUID_SERVCLASS_PUBLIC_BROWSE_GROUP;

    if (SDP_GetLocalDiRecord(&device_info, (UINT32 *)&handle) != SDP_SUCCESS) {
        tSDP_DI_RECORD *p_record = &device_info.rec;
        memset(p_record, 0, sizeof *p_record);
        device_info.rec.vendor = 15;
        device_info.rec.vendor_id_source = 1;
        device_info.rec.primary_record = TRUE;

        if (SDP_SetLocalDiRecord(p_record, (UINT32 *)&handle) != SDP_SUCCESS) {
            handle = 0;
            return FALSE;
        }
    }

    SDP_AddUuidSequence(handle, 5, 1, &browse_group);
    version[0] = BRCM_EXT_VERSION >> 8;
    version[1] = BRCM_EXT_VERSION;
    SDP_AddAttribute(handle, ATTR_ID_EXT_BRCM_VERSION, UINT_DESC_TYPE, 2, version);
    return TRUE;
}
