#ifndef RP_GRAPHICS_MODEL_RECORD_H
#define RP_GRAPHICS_MODEL_RECORD_H
#include <Pack/types_pack.h>

#include <egg/math.h>
#include <nw4r/math.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpModel;

/**
 * @brief One recorded pose (inferred name)
 */
struct RPGrpModelRecordSample {
    nw4r::math::MTX34 baseMtx;  // at 0x0
    EGG::Matrix34f* pJoints;    // at 0x30
};

/**
 * @brief Joint matrix with an out-of-line constructor (inferred)
 */
struct RPGrpModelRecordMtx : public EGG::Matrix34f {
    RPGrpModelRecordMtx();
};

/**
 * @brief Recorded pose list; the vtable pointer follows it (inferred split)
 */
struct RPGrpModelRecordFrames {
    u16 mNumFrames;                // at 0x0
    RPGrpModelRecordSample* mpSamples; // at 0x4
};

/**
 * @brief Recorded pose storage interface (inferred name)
 */
class RPGrpModelRecordBuffer : public RPGrpModelRecordFrames {
public:
    RPGrpModelRecordBuffer(u16 frames);

    virtual ~RPGrpModelRecordBuffer(); // at 0x8

    virtual void Store(RPGrpModelRecordSample* pDst,
                       const RPGrpModelRecordSample* pSrc) = 0; // at 0xC

    virtual void Lerp(RPGrpModelRecordSample* pDst,
                      const RPGrpModelRecordSample* pA,
                      const RPGrpModelRecordSample* pB, f32 t) = 0; // at 0x10

    virtual void Reset(RPGrpModelRecordSample* pSample) = 0; // at 0x14

    void ResetAll() {
        for (int i = 0; i < mNumFrames; i++) {
            Reset(&mpSamples[i]);
        }
    }
};

/**
 * @brief Recorded pose storage for a joint hierarchy (inferred name)
 */
class RPGrpModelRecordJointBuffer : public RPGrpModelRecordBuffer {
public:
    RPGrpModelRecordJointBuffer(u16 frames, u16 numJoints)
        : RPGrpModelRecordBuffer(frames), mNumJoints(numJoints) {
        for (int i = 0; i < mNumFrames; i++) {
            mpSamples[i].pJoints = new RPGrpModelRecordMtx[mNumJoints];
            for (int j = 0; j < mNumJoints; j++) {
                nw4r::math::MTX34Identity(&mpSamples[i].pJoints[j]);
            }
        }
    }

    virtual ~RPGrpModelRecordJointBuffer(); // at 0x8

    virtual void Store(RPGrpModelRecordSample* pDst,
                       const RPGrpModelRecordSample* pSrc); // at 0xC

    virtual void Lerp(RPGrpModelRecordSample* pDst,
                      const RPGrpModelRecordSample* pA,
                      const RPGrpModelRecordSample* pB, f32 t); // at 0x10

    virtual void Reset(RPGrpModelRecordSample* pSample); // at 0x14

    u16 mNumJoints; // at 0xC
};

/**
 * @brief Record state; the vtable pointer follows it in RPGrpModelRecord
 * (inferred split)
 */
struct RPGrpModelRecordState {
    u16 mFlags;                            // at 0x0
    f32 mFrame;                            // at 0x4
    RPGrpModelRecordJointBuffer* mpBuffer; // at 0x8
    RPGrpModelRecordSample mSample;        // at 0xC
    u16 mIndex;                            // at 0x40
};

/**
 * @brief Model transformation recorder
 */
class RPGrpModelRecord : private RPGrpModelRecordState {
public:
    /**
     * @brief Recorder state flags
     */
    enum EFlag {
        EFlag_Record = 1 << 0, //!< Record the model pose on the next Calc
        EFlag_Play = 1 << 1,   //!< Apply the recorded pose on the next Calc
    };

    /**
     * @brief Constructor
     *
     * @param frames Number of frames to record
     * @param pModel Owner model
     */
    RPGrpModelRecord(u16 frames, RPGrpModel* pModel);

    /**
     * @brief Destructor
     */
    virtual ~RPGrpModelRecord(); // at 0x8

    /**
     * @brief Clears the recorded data
     */
    void Clear();

    /**
     * @brief Records the current frame
     *
     * @param pModel Model to record
     */
    void Calc(RPGrpModel* pModel);
};

//! @}

#endif
