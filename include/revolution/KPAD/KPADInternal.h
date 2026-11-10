#ifndef RVL_SDK_KPAD_INTERNAL_H
#define RVL_SDK_KPAD_INTERNAL_H
#include <types.h>

#include <revolution/KPAD/KPAD.h>
#include <revolution/MTX.h>
#include <revolution/WPAD.h>

#ifdef __cplusplus
extern "C" {
#endif

// Internal KPAD types. Layout taken from Petari's kpad.h (Super Mario
// Galaxy); not yet verified against the Wii Sports binary.

#define KPAD_BUTTON_MASK 0x0000ffff
#define KPAD_BUTTON_RPT 0x80000000

#define KPAD_BTN_RPT_TIME_MAX 20000
#define KPAD_BTN_NO_RPT_DELAY 40000

#define KPAD_CMOS_RESO_WX 128
#define KPAD_CMOS_RESO_WY 96
#define KPAD_CMOS_RESO_CX (KPAD_CMOS_RESO_WX / 2)
#define KPAD_CMOS_RESO_CY (KPAD_CMOS_RESO_WY / 2)

// WPAD has no public IR image size constants in this repo
#define KPAD_DPD_RESO_WX 1024
#define KPAD_DPD_RESO_WY 768
#define KPAD_DPD_RESO_CX (KPAD_DPD_RESO_WX / 2)
#define KPAD_DPD_RESO_CY (KPAD_DPD_RESO_WY / 2)

#define KPAD_USE_OBJECTS 2

#define KPAD_RING_BUF_SIZE 16

typedef enum KPADPlayMode {
    KPAD_PLAY_MODE_LOOSE = 0,
    KPAD_PLAY_MODE_TIGHT
} KPADPlayMode;

typedef struct KPADUnifiedWpadStatus {
    union {
        WPADStatus core;
        WPADFSStatus fs;
        WPADCLStatus cl;
    } u;
    u8 fmt;
    u8 padding;
} KPADUnifiedWpadStatus;

typedef struct KPADObject {
    Vec2 center;
    s8 error_fg;
    s8 state_fg;
    s8 _fg_1;
    s8 _fg_2;
} KPADObject;

typedef union KPADTmpStatus {
    KPADStatus k;
    KPADUnifiedWpadStatus w;
} KPADTmpStatus;

typedef void (*KPADControlDpdCallback)(s32 chan, s32 reason);

typedef struct KPADInsideStatus {
    KPADStatus status;

    f32 pos_play_radius;
    f32 pos_sensitivity;

    f32 hori_play_radius;
    f32 hori_sensitivity;

    f32 dist_play_radius;
    f32 dist_sensitivity;

    f32 acc_play_radius;
    f32 acc_sensitivity;
    f32 dist_org;
    Vec2 accXY_nrm_hori;
    Vec2 sec_nrm_hori;
    Vec2 center_org;
    f32 dpd2pos_scale;
    KPADObject kobj_sample[4];
    KPADObject kobj_regular[2];
    s16 valid_objs;
    u8 bufIdx;
    u8 bufCount;
    KPADUnifiedWpadStatus uniRingBuf[KPAD_RING_BUF_SIZE];
    f32 sec_length;
    Vec2 sec_nrm;
    f32 sec_dist;
    f32 trust_sec_length;
    Vec hard_acc;
    Vec2 obj_horizon;
    Vec2 acc_horizon;
    Vec2 ah_circle_pos;
    u16 ah_circle_ct;
    u8 dpd_valid2_ct;
    s8 _fg_4;
    u16 btn_repeat_time;
    u16 btn_repeat_next;
    u16 btn_repeat_delay;
    u16 btn_repeat_pulse;
    u16 btn_cl_repeat_time;
    u16 btn_cl_repeat_next;
    KPADControlDpdCallback dpd_ctrl_callback;
    f32 acc_scale_x;
    f32 acc_scale_y;
    f32 acc_scale_z;
    f32 fs_acc_scale_x;
    f32 fs_acc_scale_y;
    f32 fs_acc_scale_z;
    Vec2 kobj_frame_min;
    Vec2 kobj_frame_max;
    f32 err_dist_speed_1;
    f32 err_dist_speedM_1;
    f32 ah_circle_radius2;
    f32 dist_vv1;
    f32 err_dist_min;
    WPADSamplingCallback appSamplingCallback;
    u8 readLocked;
    u8 resetReq;
    u8 exResetReq;
    u8 dpdIssued;
    u8 dpdEnabled;
    u8 dpdCmd;
    u8 dpdPreCallbackDone;
    u8 dpdPostCallbackDone;
} KPADInsideStatus;

void KPADReset(void);

extern KPADInsideStatus inside_kpads[];

#ifdef __cplusplus
}
#endif
#endif
