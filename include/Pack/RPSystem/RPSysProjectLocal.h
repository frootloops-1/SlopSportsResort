#ifndef RP_SYSTEM_PROJECT_LOCAL_H
#define RP_SYSTEM_PROJECT_LOCAL_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>
#include <Pack/RPSystem/RPSysSceneCreator.h>

#include <egg/core.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Runtime project localization
 */
class RPSysProjectLocal {
    RP_SINGLETON_DECL_EX(RPSysProjectLocal);

public:
    /**
     * @brief Game region
     */
    enum ERegion {
        ERegion_NTSC_J, //!< Japan
        ERegion_NTSC_U, //!< Americas/Asia
        ERegion_PAL,    //!< Europe/Oceania
        ERegion_KOR     //!< Korea
    };

    /**
     * @brief World area
     */
    enum EArea {
        EArea_England,
        EArea_France,
        EArea_Germany,
        EArea_Italy,
        EArea_Spain,
        EArea_Netherlands,
        EArea_Japan,
        EArea_USA,
        EArea_Unk8, //!< Resort: French layout (placeholder name)
        EArea_Unk9, //!< Resort: Spanish layout (placeholder name)
    };

    /**
     * @brief Target framerate
     */
    enum EFrameRate {
        EFrameRate_60Hz, //!< NTSC/PAL60 (60Hz)
        EFrameRate_50Hz, //!< PAL50 (50Hz)
    };

    /**
     * @brief Storage device
     */
    enum EStorage {
        //! Sound archives are read from the DVD as needed
        EStorage_DVDStream,
        //! Sound archives are read from the NAND ahead of time
        EStorage_NANDBuffer,
        //! Sound archives are read from the DVD ahead of time
        EStorage_DVDBuffer
    };

public:
    /**
     * @brief Resort: whether the MPLS movie (player.dol) has been played
     */
    bool isMplsMoviePlayed() const {
        return mResortSCFlags[2];
    }

    /**
     * @brief Appends the locale directory to the given path
     *
     * @param pPath Path to append to
     * @param pSuffix Optional suffix to append after the locale
     */
    void appendLocalDirectory(char* pPath, const char* pSuffix = "");

    /**
     * @brief Sets the current locale
     *
     * @param locale Locale area
     */
    void setLocale(EArea locale);

    /**
     * @brief Sets the current language
     *
     * @param lang Language area
     */
    void setLanguage(EArea lang);

    /**
     * @brief Gets the current game region
     */
    ERegion getRegion() const {
        return mRegion;
    }

    /**
     * @brief Gets the current game locale
     */
    EArea getLocale() const {
        return mLocale;
    }

    /**
     * @brief Gets the current game language
     */
    EArea getLanguage() const {
        return mLanguage;
    }

    /**
     * @brief Gets the target framerate
     */
    EFrameRate getFrameRate() const {
        return mFrameRate;
    }

private:
    // Resort layout (init 0x80230A5C): no Pack ID or sound storage fields

    //! Game region
    ERegion mRegion; // at 0x8
    //! Game locale
    EArea mLocale; // at 0xC
    //! Game language
    EArea mLanguage; // at 0x10
    //! Target framerate
    EFrameRate mFrameRate; // at 0x14
    //! Resort: [0] SCGetEULA, [1] SC simple address region ID,
    //! [2] SCGetMplsMoviePlay (set by fn_80230AE4)
    u8 mResortSCFlags[4]; // at 0x18
};

//! @}

#endif
