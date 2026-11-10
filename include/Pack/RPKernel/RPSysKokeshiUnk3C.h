#ifndef RP_KERNEL_KOKESHI_UNK3C_H
#define RP_KERNEL_KOKESHI_UNK3C_H
#include <Pack/types_pack.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Resort clothing texture table owned by RPSysKokeshiManager (member at
 * 0x3C). Placeholder name: the class is defined in the file before
 * RPSysKokeshiManager.cpp (code 0x80245B7C-0x80245FA4, vtable lbl_806B9780,
 * ctor 0x80245E1C, sizeof 4, created by RPSysResourceManager 0x80232484).
 */
class RPSysKokeshiUnk3C {
public:
    RPSysKokeshiUnk3C();
    virtual ~RPSysKokeshiUnk3C(); // at 0x8

    //! 0x80245B7C: name of the clothing archive file (.sdata 0x806F0BC8)
    const char* Unk_80245B7C() const;

    /**
     * @brief 0x80245CD4: reads a texture name pair from the table at
     * lbl_806B9520 (const char* [15][2][4])
     *
     * @param[out] ppNameA Entry [a][b][i] (ignored if NULL)
     * @param[out] ppNameB Entry [a][b][3] (ignored if NULL)
     */
    void Unk_80245CD4(u16 a, int b, int i, const char** ppNameA,
                      const char** ppNameB) const;

    //! 0x80245CAC: 1 for 10, 2 for 2 and 3, otherwise 0
    static int Unk_80245CAC(int x);
};

//! @}

#endif
