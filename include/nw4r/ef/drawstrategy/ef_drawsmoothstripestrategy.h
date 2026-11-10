#ifndef NW4R_EF_DRAW_STRATEGY_DRAW_SMOOTH_STRIPE_STRATEGY_H
#define NW4R_EF_DRAW_STRATEGY_DRAW_SMOOTH_STRIPE_STRATEGY_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/drawstrategy/ef_drawstrategyimpl.h>

#include <nw4r/math.h>

namespace nw4r {
namespace ef {

// Forward declarations
class Particle;

class DrawSmoothStripeStrategy : public DrawStrategyImpl {
public:
    struct Trigonometric {
        f32 mCos; // at 0x0
        f32 mSin; // at 0x4
    };

    struct Vertex {
        math::VEC3 mVertex0; // at 0x0
        math::VEC3 mVertex1; // at 0xC
        f32 mTexCoord;       // at 0x18

        Vertex() {}
        Vertex(const math::VEC3& rVertex0, const math::VEC3& rVertex1,
               f32 texCoord);
    };

    struct VertexTube {
        math::VEC3 mCenter; // at 0x0
        math::VEC3 mX;      // at 0xC
        math::VEC3 mZ;      // at 0x18
        f32 mTexCoord;      // at 0x24

        VertexTube() {}
        VertexTube(const math::VEC3& rCenter, const math::VEC3& rX,
                   const math::VEC3& rZ, f32 texCoord)
            : mCenter(rCenter), mX(rX), mZ(rZ), mTexCoord(texCoord) {}
    };

    struct AheadContextStripe : public AheadContext {
        math::VEC3 mEmitterAxisX;      // at 0xBC
        math::VEC3 mScreenAxisZ;       // at 0xC8
        Trigonometric* mTrigonometric; // at 0xD4

        AheadContextStripe(const math::MTX34& rViewMtx,
                           ParticleManager* pManager)
            : AheadContext(rViewMtx, pManager) {
            math::VEC3 x(mCommon.mEmitterMtx._00, mCommon.mEmitterMtx._10,
                         mCommon.mEmitterMtx._20);
            math::VEC3TransformNormal(&mEmitterAxisX,
                                     &mCommon.mParticleManagerMtxInv, &x);
        }
    };

public:
    DrawSmoothStripeStrategy();

    virtual void Draw(const DrawInfo& rInfo,
                      ParticleManager* pManager); // at 0xC

    virtual CalcAheadFunc
    GetCalcAheadFunc(ParticleManager* pManager); // at 0x18

private:
    enum PrevAxisType {
        PREVAXIS_EMITTER_Y = 0x00,
        PREVAXIS_EMITTER_X = 0x08,
        PREVAXIS_EMITTER_Z = 0x10,
        PREVAXIS_ZERO = 0x18,
        PREVAXIS__MASK = 0x38
    };

    enum StripeTexmapType { STRIPE_TEXMAP__MASK = 0xC0 };

    typedef void (*CalcAheadStripeFunc)(math::VEC3* pAxisY,
                                        AheadContextStripe* pContext,
                                        Particle* pParticle);

    int GetDrawOrder(const EmitterDrawSetting& rSetting) const;
    int GetStripeTexmapType(const EmitterDrawSetting& rSetting) const;

    math::VEC3 GetInitialPrevAxis(const EmitterDrawSetting& rSetting,
                                  const AheadContextStripe& rContext);

    static math::MTX34 CalcAxisMtx(const math::VEC3& rAxisY,
                                   AheadContextStripe* pContext, int option,
                                   Particle* pParticle,
                                   const math::VEC3& rPos);
    static math::MTX34 CalcRotMtx(Particle* pParticle, f32 px);
    static math::MTX34 CalcTubeRotMtx(Particle* pParticle,
                                      const math::VEC3& rRot, f32 px,
                                      f32 pz);

    void CalcVertex(Vertex* pVertex, AheadContextStripe* pContext, int option,
                    Particle* pParticle, CalcAheadStripeFunc pCalcAhead,
                    const math::VEC3& rPos, const math::VEC3& rVtx0,
                    const math::VEC3& rVtx1, f32 px, f32 texCoord);

    void CalcVertexTube(VertexTube* pVertex, AheadContextStripe* pContext,
                        int option, Particle* pParticle,
                        CalcAheadStripeFunc pCalcAhead, f32 px, f32 pz,
                        f32 texCoord);

    void DrawSection_BSpline(int numDiv, const Vertex& rV0, const Vertex& rV1,
                             const Vertex& rV2, int option);
    void DrawSectionEnd_BSpline(const Vertex& rV0, const Vertex& rV1,
                                const Vertex& rV2, int option);
    void DrawSectionTube_BSpline(int numDiv, int numSeg,
                                 const VertexTube& rV0, const VertexTube& rV1,
                                 const VertexTube& rV2, int option,
                                 const Trigonometric* pTrig);

    void DrawSmoothStripe_BSpline_ConnectNone(AheadContextStripe* pContext,
                                              int numDiv, int option,
                                              const math::VEC3& rVtx0,
                                              const math::VEC3& rVtx1);
    void DrawSmoothStripe_BSpline_ConnectRing(AheadContextStripe* pContext,
                                              int numDiv, int option,
                                              const math::VEC3& rVtx0,
                                              const math::VEC3& rVtx1);
    void DrawSmoothStripe_BSpline_ConnectEmitter(AheadContextStripe* pContext,
                                                 int numDiv, int option,
                                                 const math::VEC3& rVtx0,
                                                 const math::VEC3& rVtx1);

    void DrawSmoothStripe(AheadContextStripe* pContext, int numDiv,
                          int option, const math::VEC3& rVtx0,
                          const math::VEC3& rVtx1);

    void DrawSmoothStripeTube_BSpline_ConnectNone(AheadContextStripe* pContext,
                                                  int numDiv, int option);
    void DrawSmoothStripeTube_BSpline_ConnectRing(AheadContextStripe* pContext,
                                                  int numDiv, int option);
    void DrawSmoothStripeTube_BSpline_ConnectEmitter(
        AheadContextStripe* pContext, int numDiv, int option);
    void DrawSmoothStripeTube(AheadContextStripe* pContext, int numDiv,
                              int option);

    static void CalcAhead_Particle_Stripe(math::VEC3* pAxisY,
                                          AheadContextStripe* pContext,
                                          Particle* pParticle);
    static void CalcAhead_ParticleBoth_Stripe(math::VEC3* pAxisY,
                                              AheadContextStripe* pContext,
                                              Particle* pParticle);
    static void CalcAhead_ParticleBoth_Ring(math::VEC3* pAxisY,
                                            AheadContextStripe* pContext,
                                            Particle* pParticle);
    static void CalcAhead_ParticleBoth_Origin(math::VEC3* pAxisY,
                                              AheadContextStripe* pContext,
                                              Particle* pParticle);
};

} // namespace ef
} // namespace nw4r

#endif
