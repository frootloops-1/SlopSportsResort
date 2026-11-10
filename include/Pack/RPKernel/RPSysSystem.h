#ifndef RP_KERNEL_SYSTEM_H
#define RP_KERNEL_SYSTEM_H
#include <Pack/types_pack.h>

#include <Pack/RPSystem/RPSysRenderMode.h>
#include <Pack/RPSystem/RPSysSceneCreator.h>

#include <egg/core.h>

#include <nw4r/ut.h>

#include <revolution/GX.h>
#include <revolution/OS.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Pack Project configuration data.
 * @note In RSPE01_01 this object is at .bss 0x804A3D50 and is 0x50 bytes
 * (RZTE01_01: 0x807CEB60).
 */

class RPSysConfigData : public EGG::ConfigurationData {
    friend class RPSysSystem;

public:
    explicit RPSysConfigData(u32 systemHeapSize)
        : EGG::ConfigurationData(systemHeapSize) {}

    // Declared before getVideo: matches the original weak emission order
    virtual EGG::Heap* getSystemHeap() override {
        return mSystemHeap;
    }
    virtual EGG::Video* getVideo() override {
        return mVideo;
    }
    virtual EGG::Display* getDisplay() override {
        return mDisplay;
    }
    virtual EGG::XfbManager* getXfbMgr() override {
        return mXfbMgr;
    }
    virtual EGG::PerformanceView* getPerfView() override {
        return mPerfView;
    }
    virtual EGG::SceneManager* getSceneMgr() override {
        return mSceneMgr;
    }
    virtual EGG::IAudioMgr* getAudioMgr() override {
        return mAudioMgr;
    }

private:
    EGG::Video* mVideo;           // at 0x38
    EGG::XfbManager* mXfbMgr;     // at 0x3C
    EGG::Display* mDisplay;       // at 0x40
    EGG::PerformanceView* mPerfView; // at 0x44
    EGG::SceneManager* mSceneMgr;    // at 0x48
    EGG::IAudioMgr* mAudioMgr;       // at 0x4C
};

/**
 * @brief Pack Project engine system
 */
class RPSysSystem {
    friend class RPSysConfigData;

public:
    /**
     * @brief Gets this class's singleton instance
     */
    static RPSysSystem* instance() {
        return spInstance;
    }

    /**
     * @brief Auto-detects the screen's aspect ratio
     */
    static void setupTVMode() DECOMP_DONT_INLINE;
    /**
     * @brief Auto-detects the render mode and progressive setting
     */
    static void setupRenderMode();

    /**
     * @brief Initializes the RP engine and its core components
     */
    static void initialize();

    /**
     * @brief Creates this class's singleton instance
     */
    static void create();

    /**
     * @brief Gets the width of the framebuffer, in pixels
     */
    u16 getFBWidth() const {
        return spRenderModeObj->fbWidth;
    }
    /**
     * @brief Gets the height of the framebuffer, in pixels
     */
    u16 getFBHeight() const {
        return spRenderModeObj->efbHeight;
    }

    /**
     * @brief Loads the Pack Project build timestamp from the disc
     */
    void createTimeStamp();
    /**
     * @brief Creates a work buffer for the effect manager
     */
    void createEffectWork();
    /**
     * @brief Creates the engine's core components using the system heap
     */
    void createFromSystemHeap();

    /**
     * @brief Prepares the engine for the first frame
     */
    void setup();
    /**
     * @brief Enters the engine's main loop
     */
    void mainLoop();

    /**
     * @brief Gets the ID of the boot scene
     */
    RPSysSceneCreator::ESceneID getBootScene();

    /**
     * @brief Gets the current clock time represented as a 32-bit calendar time
     */
    RPTime32 getCalendarTime32();
    /**
     * @brief Gets the current clock time represented as a 16-bit calendar time
     */
    RPTime16 getCalendarTime16();

    /**
     * @brief Splits 32-bit calendar time into parts
     * @note If no input time is specified, this function operates on the
     * current clock time.
     *
     * @param pTime32 Input time
     * @param rYear Year
     * @param rMon Month (one-indexed)
     * @param rMDay Day of the month
     * @param rHour Hour
     * @param rMin Minute
     */
    void getCalendarTime(const RPTime32* pTime32, u32& rYear, u32& rMon,
                         u32& rMDay, u32& rHour, u32& rMin);

    /**
     * @brief Splits 16-bit calendar time into parts
     * @note If no input time is specified, this function operates on the
     * current clock time.
     *
     * @param pTime16 Input time
     * @param rYear Year
     * @param rMon Month (one-indexed)
     * @param rMDay Day of the month
     */
    void getCalendarTime(const RPTime16* pTime16, u32& rYear, u32& rMon,
                         u32& rMDay);

    /**
     * @brief Shuts down the engine and exits the application
     * @details Depending on the instructions from the scene manager, this will
     * either exit to the system menu or shutdown the console.
     */
    void systemShutDown();

    /**
     * @brief Updates the system state during resource loading
     *
     * @param hide Disable "Now Loading" text
     */
    void loadFrameWork(bool hide);

    /**
     * @brief Gets the number of ticks per frame
     */
    u8 getFrameRate() const;
    /**
     * @brief Gets the modify ratio of the display
     */
    f32 getModifyRatio() const;

    /**
     * @brief Sets the background clear color of the EFB
     *
     * @param color Clear color
     */
    void setDisplayClearColor(nw4r::ut::Color color);

    /**
     * @brief Destroys the specified heap
     *
     * @param pHeap Heap to destroy
     * @param unused Resort: unused flag (callers pass true or a bool member)
     */
    void destroyHeap(EGG::Heap* pHeap, bool unused);

    /**
     * @brief Allocates memory from the specified heap
     *
     * @param pHeap Heap to allocate from
     * @param size Amount of memory required
     * @param align Required byte-alignment
     * @return void* Allocated memory block
     */
    void* alloc(EGG::Heap* pHeap, u32 size, s32 align = 4) {
        return EGG::Heap::alloc(size, align, pHeap);
    }

    /**
     * @brief Frees memory to the specified heap
     *
     * @param pHeap Heap to free to
     * @param pBlock Memory block to free
     */
    void free(EGG::Heap* pHeap, void* pBlock) {
        return EGG::Heap::free(pBlock, pHeap);
    }

    /**
     * @brief Initializes the load count to zero frames
     */
    void startLoadCount();
    /**
     * @brief Tests whether the current load count is over five seconds (600f)
     */
    bool isLoadCountEnd() const;

    /**
     * @brief Turns on/off screen dimming
     * @note If "Screen Saver Mode" is disabled, dimming is always OFF.
     *
     * @param dim Whether to dim the screen
     */
    void setDimming(BOOL dim);

    /**
     * @brief Gets the heap for the resource manager
     */
    EGG::Heap* getResourceHeap() const {
        return mpResourceHeap;
    }

    // Resort: parent heaps of the scene heaps (RPSysScene 0x8022FCD4)
    EGG::Heap* getUnkHeap10() const {
        return mpUnkHeap10;
    }
    EGG::Heap* getUnkHeap14() const {
        return mpUnkHeap14;
    }

    /**
     * @brief Gets the thread for asynchronous NAND operations
     */
    // Resort: 0x80237918, does not use this; returns a float at +0x9C of sConfigData.mDisplay.
    // Called on the singleton by RPGrpCamera. Name not proven.
    f32 Unk_80237918() const;

    EGG::TaskThread* getNandThread() {
        return mpTaskThreadInfo->pNandThread;
    }
    /**
     * @brief Gets the thread for asynchronous disc operations
     */
    EGG::TaskThread* getDvdThread() {
        return mpTaskThreadInfo->pDvdThread;
    }
    /**
     * @brief Gets the thread for asynchronous WiiConnect24 operations
     */
    EGG::TaskThread* getWc24Thread() {
        return mpTaskThreadInfo->pWc24Thread;
    }

    /**
     * @brief Gets the task-end thread message for asynchronous NAND operations
     */
    OSMessage getNandEndMessage() {
        return (OSMessage)&mpTaskThreadInfo->nandEndMessage;
    }
    /**
     * @brief Gets the task-end thread message for asynchronous disc operations
     */
    OSMessage getDvdEndMessage() const;

    /**
     * @brief Gets the Pack Project build information
     */
    const char* getTimeStampString();

    /**
     * @brief Auto-detects project locale settings
     */
    void setupLocalSettings();

    /**
     * @brief Blocks the main thread until it is safe to change the render mode
     * @details Waits for either 100 frames or 1.6 seconds to pass.
     *
     * @history This arbitrary 1.6 second delay is likely from performance
     * metrics taken during development. This code exists in other EAD games
     * (notably Big Brain Academy and Mario Kart Wii), where the delay is
     * slightly changed.
     */
    void waitRenderModeChange() DECOMP_DONT_INLINE;

    /**
     * @brief Installs reset and shutdown callbacks to the OS
     */
    void setCallBack();

    //! @name Resort functions (names not proven)
    //! @{
    void Unk_8022DC18();
    void Unk_8022D88C();
    EGG::Heap* Unk_8022D650(EGG::Heap* pParent, s32 kind, u32 size, BOOL clear,
                            u32 unitSize, BOOL unused) DECOMP_DONT_INLINE;
    void Unk_8022D5E4();
    void Unk_8022D5D4(u8 value);
    void Unk_8022D594();
    void Unk_8022D518();
    void Unk_8022D494();
    bool Unk_8022D440();
    //! @}

    static RPSysConfigData* getConfigData() {
        return &sConfigData;
    }

private:
    /**
     * @brief Constructor
     */
    RPSysSystem();
    /**
     * @brief Destructor
     */
    virtual ~RPSysSystem(); // at 0x8

    /**
     * @brief OS reset callback
     */
    static void softResetCallBack();
    /**
     * @brief OS shutdown callback
     */
    static void shutdownSystemCallBack();

    /**
     * @brief DVDCheckDiskAsync callback (Resort, unnamed)
     */
    static void Unk_8022D328(s32 result, DVDCommandBlock* pBlock);

    /**
     * @brief Makes the specified heap current, saving the previous one
     */
    void lockHeap(EGG::Heap* pHeap) {
        OSLockMutex(&mCurrentHeapMutex);
        mpCurrentHeap = EGG::Heap::getCurrentHeap();
        pHeap->becomeCurrentHeap();
    }

private:
    /**
     * @brief Task threads for asynchronous NAND/disc/WiiConnect24 work
     * @note Resort: 0x18-byte object owned at 0x4C. Its ctor (0x8023873C) and
     * thread setup (0x802386A8) live outside this file. Class name not proven.
     */
    struct Unk_8023873C {
        Unk_8023873C();
        //! Creates the three task threads and their shared end message queue
        void Unk_802386A8();

        EGG::TaskThread* pNandThread; // at 0x0
        EGG::TaskThread* pDvdThread;  // at 0x4
        EGG::TaskThread* pWc24Thread; // at 0x8
        u32 nandEndMessage;           // at 0xC ('nand')
        u32 dvdEndMessage;            // at 0x10 ('disk')
        u32 wc24EndMessage;           // at 0x14 ('nwc_')
    };

private:
    //! Heap created by Unk_8022DC18 (MEM2, 0x200000)
    EGG::Heap* mpUnkHeap04; // at 0x4
    //! Heap used by the resource manager
    EGG::Heap* mpResourceHeap; // at 0x8
    //! Resource cache heap ("resCache")
    EGG::Heap* mpResCacheHeap; // at 0xC
    //! Heap created by Unk_8022DC18 (MEM1, 0x580000)
    EGG::Heap* mpUnkHeap10; // at 0x10
    //! Heap created by Unk_8022DC18 (MEM1, 0x400000), not cleared by the ctor
    EGG::Heap* mpUnkHeap14; // at 0x14
    //! Heap used for error handling when other heaps are exhausted
    EGG::Heap* mpAssertHeap; // at 0x18
    EGG::Heap* mpUnkHeap1C; // at 0x1C
    EGG::Heap* mpUnkHeap20; // at 0x20
    EGG::Heap* mpUnkHeap24; // at 0x24
    //! Heap holding the rest of MEM1
    EGG::Heap* mpUnkHeap28; // at 0x28
    //! Heap holding the rest of MEM2
    EGG::Heap* mpUnkHeap2C; // at 0x2C

    //! Backup of the EGG current heap while it is changed
    EGG::Heap* mpCurrentHeap; // at 0x30
    //! Mutex to guard changing the current heap
    OSMutex mCurrentHeapMutex; // at 0x34

    //! Asynchronous task threads
    Unk_8023873C* mpTaskThreadInfo; // at 0x4C

    //! Set by Unk_8022D5E4; softResetCallBack only handles a reset when set
    u8 mUnk50; // at 0x50
    //! Read by fn_80237910 (gates both OS callbacks), cleared by fn_802378BC
    u8 mUnk51; // at 0x51
    //! Number of ticks per frame (set with the display's by fn_80237624)
    u8 mFrameRate; // at 0x52
    //! Average frame duration, in seconds (assumes 60fps)
    f32 mFrameTime; // at 0x54
    //! Total number of frames spent loading resources
    u32 mLoadCount; // at 0x58

    //! Pack Project build information
    char* mpTimeStampString; // at 0x5C
    // Resort: sizeof(RPSysSystem) == 0x60 (create)

    //! Engine configuration
    static RPSysConfigData sConfigData;

    //! Active render mode
    static GXRenderModeObj* spRenderModeObj;
    //! Render mode format
    static RPSysRenderMode::EFormat sRenderModeFormat;
    //! @brief Time (in milliseconds) when the render mode was setup
    //! @remark This value is only non-zero when scan mode/TV format is changed
    //! and the system must wait.
    static u32 sRenderModeWaitStart;

    //! Class singleton instance
    static RPSysSystem* spInstance;

    //! Disc check state (Resort, names not proven)
    enum EDiskCheck {
        EDiskCheck_Busy,
        EDiskCheck_Ok,
        EDiskCheck_Error,
    };

    //! Result of the disc check started by Unk_8022D440
    static EDiskCheck sDiskCheckResult;
    //! MEM2 memory used by the external framebuffers
    static u32 sXfbMemorySize;
    //! MEM1 memory used by the effect manager work
    static u32 sEffectMemorySize;
};

//! @}

#endif
