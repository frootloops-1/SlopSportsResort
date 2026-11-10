#ifndef RP_SYSTEM_SAVE_DATA_MGR_H
#define RP_SYSTEM_SAVE_DATA_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel.h>
#include <Pack/RPSingleton.h>
#include <Pack/RPSystem/RPPartyPlayerData.h>
#include <Pack/RPSystem/RPPartySystemData.h>
#include <Pack/RPSystem/RPSportsPlayerData.h>
#include <Pack/RPSystem/RPSportsSystemData.h>

#include <egg/core.h>

#include <revolution/OS.h>

//! @addtogroup rp_system
//! @{

// Forward declarations
class RPSysSaveData;

/**
 * @brief Save data manager
 */
class RPSysSaveDataMgr : public IRPSysHostIOSocket {
    RP_SINGLETON_DECL_EX(RPSysSaveDataMgr);

public:
    /**
     * @brief Banner file type
     */
    enum EBannerType {
        EBannerType_Real, //!< Banner file in the home directory
        EBannerType_Temp, //!< Banner file in the temporary directory

        EBannerType_Max
    };

public:
    /**
     * @name Access save data
     */
    /**@{*/
    /**
     * @brief Gets the Sports Pack player data at the specified player list
     * index
     *
     * @param idx Player list index
     */
    RPSportsPlayerData getSportsPlayerData(s32 idx) const;
    /**
     * @brief Sets the Sports Pack player data at the specified player list
     * index
     *
     * @param rPlayerData Player data
     * @param idx Player list index
     */
    void setSportsPlayerData(const RPSportsPlayerData& rPlayerData, s32 idx);

    /**
     * @brief Gets the Sports Pack system data
     */
    RPSportsSystemData getSportsSystemData() const;
    /**
     * @brief Sets the Sports Pack system data
     *
     * @param rSystemData System data
     */
    void setSportsSystemData(const RPSportsSystemData& rSystemData);

    /**
     * @brief Gets the Party Pack player data at the specified player list
     * index
     *
     * @param idx Player list index
     */
    RPPartyPlayerData getPartyPlayerData(s32 idx) const;
    /**
     * @brief Sets the Party Pack player data at the specified player list
     * index
     *
     * @param rPlayerData Player data
     * @param idx Player list index
     */
    void setPartyPlayerData(const RPPartyPlayerData& rPlayerData, s32 idx);

    /**
     * @brief Gets the Party Pack system data
     */
    RPPartySystemData getPartySystemData() const;
    /**
     * @brief Sets the Party Pack system data
     *
     * @param rSystemData System data
     */
    void setPartySystemData(const RPPartySystemData& rSystemData);
    /**@}*/

    /**
     * @name Prepare save data
     */
    /**@{*/
    /**
     * @brief Checks which save data files exist on the NAND (asynchronous)
     *
     * @return Success
     */
    bool existPackFileAsync();
    /**
     * @brief Tests whether the NAND has enough free space to store both the
     * banner and save files (asynchronous)
     *
     * @return Success
     */
    bool existNandMemoryAsync();

    /**
     * @brief Attempts to create both the banner and save files on the NAND
     * (asynchonous)
     *
     * @return Success
     */
    bool createPackFileAsync();
    bool deletePackFileAsync();
    /**
     * @brief Attempts to load the save file from the NAND (asynchronous)
     *
     * @return Success
     */
    bool loadAsync();
    /**
     * @brief Attempts to save both the banner and save files to the NAND
     * (asynchronous)
     *
     * @return Success
     */
    bool saveAsync();

    /**
     * @name State checking
     */
    /**@{*/
    /**
     * @brief Tests whether async operations have completed
     */
    bool isAsyncFinish() const;
    /**
     * @brief Tests whether NAND operations have completed
     */
    bool isNandAccessFinish() const;

    /**
     * @brief Tests whether both the banner and save files exist on the NAND
     */
    bool isPackFileExist() const;
    /**
     * @brief Tests whether the NAND has enough free space to store both the
     * banner and save files
     */
    bool isNandMemoryExist() const;

    /**
     * @brief Tests whether the save file is broken (bad magic, checksum, etc.)
     */
    bool isSaveFileBroken() const;
    /**
     * @brief Tests whether any unrecoverable error has occurred
     * @typo
     */
    bool isErrorOccured() const;
    /**@}*/

    /**
     * @brief Toggles the ability to save both the banner and save files to the
     * NAND
     *
     * @param disable Whether to disable saving
     */
    void setSaveDisable(bool disable);

    /**
     * @name NAND
     */
    /**@{*/
    /**
     * @brief Gets the result of the last NAND memory check
     */
    u32 getNandCheckAnswer() const;
    /**
     * @brief Gets the result of the last NAND operation
     */
    s32 getErrorCode() const;

    /**
     * @brief Gets the number of free NAND blocks needed to store both the
     * banner and save files
     */
    u32 getUserBlockSize() const;
    /**
     * @brief Gets the number of free NAND inodes needed to store both the
     * banner and save files
     */
    u32 getSaveFileNum() const;

    /**
     * @brief Marks the current async NAND operations as completed
     */
    void finishNandAccess();
    void resetSaveData();
    /**@}*/

    /**
     * @brief Updates the save manager state
     *
     * @param display Whether the scene is fully displayed
     */
    void update(bool display);

    /**
     * @brief Initializes the banner file binary
     */
    void initBanner();

    // Resort-only, unnamed
    void fn_802336BC();
    static s32 fn_802341A8(u32 answer);
    void fn_802341D8(u32 idx, const RPSportsPlayerData* pPlayerData);
    RPSportsPlayerData* fn_8023439C(u32 idx);
    void fn_802343B8(const RPSportsSystemData* pSystemData);
    RPSportsSystemData* fn_80234544();

private:
    /**
     * @brief Bitflag indices
     */
    enum {
        EFlag_NandMemoryExist, //!< Enough NAND memory exists for all files
        EFlag_BannerFileExist, //!< The banner file exists on the NAND
        EFlag_SaveFileExist,   //!< The save file exists on the NAND
        EFlag_3,
        EFlag_DisableSave, //!< Saving is disabled
        EFlag_5,
        EFlag_6,
        EFlag_7,
        EFlag_NandAccess,  //!< NAND operation is happening on another thread
        EFlag_AsyncSave,   //!< Save file is being written on another thread
        EFlag_ErrorWindow, //!< System window error was displayed
        EFlag_11,
        EFlag_NandError, //!< Unrecoverable NAND error
        EFlag_13,
        EFlag_14,
    };

    /**
     * @brief banner.tpl file indices
     */
    enum ETplIndex {
        ETplIndex_BannerTexture, //!< Banner texture
        ETplIndex_IconTexture,   //!< Icon texture
    };

    //! VF work memory size
    static const u32 VF_WORK_SIZE = OS_MEM_KB_TO_B(16);

    //! NAND save file banner size
    static const u32 SAVE_BANNER_SIZE = NAND_BANNER_SIZE(1);

    //! Number of files written when saving
#if defined(PACK_SPORTS)
    static const u32 SAVE_FILE_NUM = 2; // RPSports.dat, banner.bin
#elif defined(PACK_PARTY)
    static const u32 SAVE_FILE_NUM = 2; // RPParty.dat, banner.bin
#endif

    //! Number of icon texture frames in the save banner
    static const u32 BANNER_ICON_FRAME_NUM = 1;

private:
    //! Save file buffer wrapper (Resort `RPSysSaveData`, unnamed)
    //! Save file image (Resort layout, unnamed)
    struct SaveFile {
        u8 unk0[0x10];                         // at 0x0
        RPSportsSystemData systemData;         // at 0x10
        RPSportsPlayerData playerData[100];    // at 0x82BC
    };

    struct SaveBuffer {
        u32 size;          // at 0x0
        u32 unk4;          // at 0x4
        SaveFile* pBuffer; // at 0x8
    };

private:
    void showErrorWindow();
    void showBusyWindow();
    void clearError();
    bool prepareAccess(bool arg);
    bool requestNandFunc(void (*pFunc)(void*), bool arg);

    bool existNandMemorySync() DECOMP_DONT_INLINE;
    bool existBannerFile();
    bool existSaveFile();
    bool createBannerFile();
    bool createSaveFile();
    bool deleteBannerFile();
    bool deleteSaveFile();
    bool saveSync();
    bool loadSync();
    bool saveBannerFile(EBannerType type);

    static void existPackFileFunc(void* pArg);
    static void existNandMemoryFunc(void* pArg);
    static void createPackFileFunc(void* pArg);
    static void deletePackFileFunc(void* pArg);
    static void loadDataFunc(void* pArg);
    static void saveDataFunc(void* pArg);

private:
    //! Banner file names
    static const char* BANNER_FILE_NAMES[EBannerType_Max];
    //! Save file name
    static const char* SAVE_FILE_NAME;

    //! Status flags
    EGG::TBitFlag<u32> mFlags; // at 0x8
    //! Unrecoverable error occurred
    bool mbError; // at 0xC
    //! Last NAND operation result
    s32 mNandErrorCode; // at 0x10
    //! NANDCheck result
    u32 mNandCheckAnswer; // at 0x14
    //! Save data validation failure bits
    u32 mSaveCheckFlags; // at 0x18
    //! Save banner (`banner.bin`) size
    u32 mBannerFileSize; // at 0x1C
    //! Size of both the save file and banner together
    u32 mClusterFileSize; // at 0x20
    //! Banner file binary
    NANDBanner* mpBannerFile; // at 0x24
    //! Save file buffer
    SaveBuffer* mpSaveData; // at 0x28
};

//! @}

#endif
