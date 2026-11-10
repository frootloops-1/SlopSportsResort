#ifndef EGG_CORE_ASYNC_DISPLAY_H
#define EGG_CORE_ASYNC_DISPLAY_H
#include <egg/types_egg.h>

#include <egg/core/eggDisplay.h>

#include <nw4r/ut.h>

#include <revolution/OS.h>

namespace EGG {

class AsyncDisplay : public Display {
public:
    explicit AsyncDisplay(u8 frameRate);

    virtual void beginFrame();  // at 0x8
    virtual void beginRender(); // at 0xC
    virtual void endRender();   // at 0x10

    virtual u32 getTickPerFrame(); // at 0x18

    void postVRetrace();
    void clearEFB();

    f32 getTimeScale() const {
        return mTimeScale;
    }

private:
    enum SyncMode {
        SYNC_MODE_NONE,
        SYNC_MODE_NTSC,
    };

private:
    void calcS();
    void syncTick();

    void clearEFB(u16 fbWidth, u16 fbHeight, u16 x, u16 y, u16 width,
                  u16 height, nw4r::ut::Color color);

private:
    // Resort: 0xC0 bytes. AsyncDisplay(u8) (0x801CA924) inits the thread
    // queue at 0x60, a 4-entry message queue at 0x68 (buffer 0x88) and the
    // alarm at 0x30; zeroes 0x98/0xA4/0xA8/0xAC/0xB8, 1.0f at 0x9C.
    OSAlarm mSyncAlarm;          // at 0x30
    OSThreadQueue mSyncQueue;    // at 0x60
    OSMessageQueue mMesgQueue;   // at 0x68
    OSMessage mMesgBuffer[4];    // at 0x88
    SyncMode mSyncMode;          // at 0x98
    f32 mTimeScale;              // at 0x9C
    u32 mUnkA0;                  // at 0xA0
    u32 mUnkA4;                  // at 0xA4
    u32 mUnkA8;                  // at 0xA8
    u32 mUnkAC;                  // at 0xAC
    u32 mUnkB0;                  // at 0xB0
    u32 mUnkB4;                  // at 0xB4
    u32 mUnkB8;                  // at 0xB8
    u32 mUnkBC;                  // at 0xBC
};

} // namespace EGG

#endif
