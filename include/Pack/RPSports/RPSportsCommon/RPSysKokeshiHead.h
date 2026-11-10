#ifndef RP_SPORTS_COMMON_KOKESHI_HEAD_H
#define RP_SPORTS_COMMON_KOKESHI_HEAD_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel/IRPSysHostIOSocket.h>
#include <Pack/RPKernel/RPSysKokeshi.h>

#include <nw4r/math.h>

//! @addtogroup rp_sports
//! @{

/**
 * @brief Menu Mii (head and body models with a debug host IO socket)
 *
 * Layout confirmed against the matched RPSysKokeshiHead.cpp (size 0xF8).
 */
class RPSysKokeshiHead : public RPSysKokeshi, public IRPSysHostIOSocket {
public:
    explicit RPSysKokeshiHead(const RPSysKokeshiGenInfo* pGenInfo);
    virtual ~RPSysKokeshiHead(); // at 0x8

    // Inferred accessor (RPSysMenuKokeshiMgr reads the additional info at 0x68)
    const RFLAdditionalInfo& GetAdditionalInfo() const {
        return mAdditionalInfo;
    }

private:
    u32 mFlags;                // at 0xB8
    nw4r::math::VEC3 mScale;   // at 0xBC
    nw4r::math::MTX34 mMtx;    // at 0xC8
};

//! @}

#endif
