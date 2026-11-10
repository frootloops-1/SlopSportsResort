#ifndef RP_KERNEL_TAG_PROCESSOR_H
#define RP_KERNEL_TAG_PROCESSOR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

#include <nw4r/ut.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Wide-char text tag processor
 */
class RPSysTagProcessor : public nw4r::ut::WideTagProcessor {
    RP_SINGLETON_DECL(RPSysTagProcessor);

public:
    virtual Operation Process(u16 ch, ContextType* pCtx);
    virtual Operation CalcRect(nw4r::ut::Rect* pRect, u16 ch,
                               ContextType* pCtx);

    void PreProcessEx(wchar_t const*, wchar_t*, u32, int*, int, va_list);

    void PreProcessEx(wchar_t const*, wchar_t*, u32, int*, int, ...);

private:
    Operation fn_8019AC44(nw4r::ut::Rect* pRect, u16 ch, ContextType* pCtx);
    void fn_8019A780(nw4r::ut::Rect* pRect, ContextType* pCtx, u8 len,
                     void* pParam);
};

//! @}

#endif
