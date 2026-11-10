#ifndef RP_KERNEL_I_HOST_IO_SOCKET_H
#define RP_KERNEL_I_HOST_IO_SOCKET_H
#include <Pack/types_pack.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Host I/O socket
 */
class IRPSysHostIOSocket {
public:
    /**
     * @brief Constructor
     *
     * @param pName Socket name
     * @param ... Format string arguments
     */
    IRPSysHostIOSocket(const char* pName, ...);
    /**
     * @brief Constructor
     */
    IRPSysHostIOSocket();

    // Resort: no virtual destructor. The base vtable (0x806B9250) holds only
    // ListenPropertyEvent and GenMessage; derived classes append their own
    // virtual destructor after them (e.g. __vt__16RPSysSaveDataMgr).

    /**
     * @brief Handles property events from the host
     */
    virtual void ListenPropertyEvent() { // at 0x8
        // Stubbed for release
    }

    /**
     * @brief Generates UI control messages for the host
     */
    virtual void GenMessage() { // at 0xC
        // Stubbed for release
    }

    /**
     * @brief Destructor
     */
};

//! @}

#endif
