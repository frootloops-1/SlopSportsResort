#ifndef EGG_CORE_XFB_MANAGER_H
#define EGG_CORE_XFB_MANAGER_H
#include <egg/types_egg.h>

namespace EGG {

// Forward declarations
class Xfb;

class XfbManager {
public:
    XfbManager()
        : mQueueFront(NULL),
          mQueueEnd(NULL),
          mUnk08(NULL),
          mUnk0C(0),
          mUnk0D(0) {}

    bool attach(Xfb* pXfb);
    void copyEFB(bool clearEfb);
    void setNextFrameBuffer();
    void postVRetrace();

private:
    Xfb* mQueueFront; // at 0x0
    Xfb* mQueueEnd;   // at 0x4

    // Resort: 0x10 bytes (inline ctor in RPSysSystem::initialize zeroes three
    // words and two bytes; attach 0x801C79F8 increments both bytes)
    Xfb* mUnk08;   // at 0x8
    u8 mUnk0C;     // at 0xC
    u8 mUnk0D;     // at 0xD
};

} // namespace EGG

#endif
