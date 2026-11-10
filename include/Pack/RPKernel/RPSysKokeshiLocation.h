#ifndef RP_KERNEL_KOKESHI_LOCATION_H
#define RP_KERNEL_KOKESHI_LOCATION_H
#include <Pack/types_pack.h>

#include <RVLFaceLib.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class RPSysMiddleDB;

/**
 * @brief Mii storage location
 */
class RPSysKokeshiLocation {
public:
    /**
     * @brief Constructor
     */
    RPSysKokeshiLocation();

    /**
     * @brief Destructor
     */
    virtual ~RPSysKokeshiLocation(); // at 0x8

    // Resort: the vptr is at 0x0 (GetAdditionalInfo 0x802460EC and
    // CreateNigaoeModel 0x8024640C read the source at 0x4, the index at 0x8
    // and the middle DB at 0xC)

private:
    //! The database where this Mii exists
    RFLDataSource mDataSource; // at 0x4
    //! The Mii's index in the database
    u16 mIndex; // at 0x8

    //! Middle database where this Mii exists (only for RFLDataSource_Middle)
    RPSysMiddleDB* mpMiddleDB; // at 0xC

public:

    /**
     * @brief Gets the data source where this Mii exists
     */
    RFLDataSource GetDataSource() const {
        return mDataSource;
    }

    /**
     * @brief Sets the data source where this Mii exists
     *
     * @param src New data source
     */
    void SetDataSource(RFLDataSource src) {
        mDataSource = src;
    }

    /**
     * @brief Gets the index of this Mii in its database
     */
    u16 GetIndex() const {
        return mIndex;
    }

    /**
     * @brief Sets the index of this Mii in its database
     *
     * @param index New index
     */
    void SetIndex(u16 index) {
        mIndex = index;
    }

    /**
     * @brief Accesses the middle database where this Mii exists
     * @details If the data source is not `RFLDataSource_Middle`, this should be
     * NULL.
     */
    RPSysMiddleDB* GetMiddleDB() const {
        return mpMiddleDB;
    }

    /**
     * @brief Sets the middle database where this Mii exists
     */
    void SetMiddleDB(RPSysMiddleDB* pMiddleDB) {
        mpMiddleDB = pMiddleDB;
    }
};

//! @}

#endif
