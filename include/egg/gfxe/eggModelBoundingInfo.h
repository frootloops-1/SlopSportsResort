#ifndef EGG_GFXE_MODEL_BOUNDING_INFO_H
#define EGG_GFXE_MODEL_BOUNDING_INFO_H
#include <egg/types_egg.h>

#include <egg/prim.h>

#include <nw4r/math.h>

extern char lbl_803798F8[];

namespace EGG {

extern char sAABBAssertion[6];
extern char sSphereAssertion[8];

// Forward declarations
class ModelEx;

class ModelBoundingInfo {
public:
    enum BoundFlag {
        cBoundFlag_AABB = 1 << 0,
        cBoundFlag_AABBSet = 1 << 1,
        cBoundFlag_Sphere = 1 << 2,
        cBoundFlag_SphereSet = 1 << 3,
    };

    struct SphereShape {
        f32 r;                   // at 0x0
        nw4r::math::VEC3 center; // at 0x4
    };

    struct AABBShape {
        nw4r::math::VEC3 min; // at 0x0
        nw4r::math::VEC3 max; // at 0xC
    };

private:
    template <typename TShape> struct TData {
        TShape m_shape;
        TShape* m_pShapeSet;
    };

private:
    ModelEx* m_pMdl; // at 0x0
    f32 unk4;
    TData<AABBShape>* m_pBV;       // at 0x8
    TData<AABBShape>* m_pAABB;     // at 0xC
    TData<SphereShape>* m_pSphere; // at 0x10

public:
    ModelBoundingInfo(u32 flags, ModelEx* pMdl);
    virtual ~ModelBoundingInfo(); // at 0x8

    void calc();

    SphereShape& getShapeSphere() const {
#line 99
        EGG_ASSERT(m_pSphere);
        return m_pSphere->m_shape;
    }

private:
    template <typename TShape> TData<TShape>* createShape(bool shapeSet);
    template <typename TShape> void deleteShape(TData<TShape>* pData);

    void setAABB(TData<AABBShape>* pAABB, const nw4r::math::VEC3& rMin,
                 const nw4r::math::VEC3& rMax) {
#line 214
        EGG_ASSERT_MSG(pAABB, sAABBAssertion);

        if (rMin.x < pAABB->m_shape.min.x) {
            pAABB->m_shape.min.x = rMin.x;
        }
        if (rMax.x > pAABB->m_shape.max.x) {
            pAABB->m_shape.max.x = rMax.x;
        }

        if (rMin.y < pAABB->m_shape.min.y) {
            pAABB->m_shape.min.y = rMin.y;
        }
        if (rMax.y > pAABB->m_shape.max.y) {
            pAABB->m_shape.max.y = rMax.y;
        }

        if (rMin.z < pAABB->m_shape.min.z) {
            pAABB->m_shape.min.z = rMin.z;
        }
        if (rMax.z > pAABB->m_shape.max.z) {
            pAABB->m_shape.max.z = rMax.z;
        }
    }
    static void calcOBB(AABBShape* pOut, const nw4r::math::VEC3& rMin,
                        const nw4r::math::VEC3& rMax,
                        nw4r::math::VEC3* const* ppBases) {
        AABBShape box;
        box.min = rMin;
        box.max = rMax;
        nw4r::math::VEC3 diag;
        nw4r::math::VEC3Sub(&diag, &box.max, &box.min);

        const nw4r::math::VEC3* bz;
        const nw4r::math::VEC3* by;
        const nw4r::math::VEC3* bx;
        by = ppBases[1];
        bz = ppBases[2];
        bx = ppBases[0];
        f32 ext[3];
        ext[0] = nw4r::math::FAbs(nw4r::math::VEC3Dot(&diag, bx));
        ext[1] = nw4r::math::FAbs(nw4r::math::VEC3Dot(&diag, by));
        ext[2] = nw4r::math::FAbs(nw4r::math::VEC3Dot(&diag, bz));

        *pOut = box;

        for (int i = 0; i < 8; i++) {
            nw4r::math::VEC3 p;

            if (i < 6) {
                f32 sign = i < 3 ? 1.0f : -1.0f;
                int j = i % 3;
                f32 s = ext[j];
                s *= sign;
                nw4r::math::VEC3Scale(&p, ppBases[j], s);
                nw4r::math::VEC3Add(&p, i < 3 ? &box.min : &box.max, &p);
            } else {
                p.x = (i == 6 ? box.min : box.max).x;
                p.y = (i == 6 ? box.min : box.max).y;
                p.z = (i == 6 ? box.min : box.max).z;
            }

            if (p.x < pOut->min.x) {
                pOut->min.x = p.x;
            } else if (p.x > pOut->max.x) {
                pOut->max.x = p.x;
            }

            if (p.y < pOut->min.y) {
                pOut->min.y = p.y;
            } else if (p.y > pOut->max.y) {
                pOut->max.y = p.y;
            }

            if (p.z < pOut->min.z) {
                pOut->min.z = p.z;
            } else if (p.z > pOut->max.z) {
                pOut->max.z = p.z;
            }
        }
    }

    void setSphere(SphereShape* pSphere, const nw4r::math::VEC3& rMin,
                   const nw4r::math::VEC3& rMax) {
#line 191
        EGG_ASSERT_MSG(pSphere, sSphereAssertion);

        pSphere->center.x = (rMax.x + rMin.x) / 2;
        pSphere->center.y = (rMax.y + rMin.y) / 2;
        pSphere->center.z = (rMax.z + rMin.z) / 2;

        nw4r::math::VEC3 dir(rMax.x - rMin.x, rMax.y - rMin.y, rMax.z - rMin.z);
        pSphere->r = 0.5f * nw4r::math::VEC3Len(&dir);
    }

};

} // namespace EGG

// Included after the class: the parse order of the inline asserts sets the
// order of their weak @STRING@ objects in .data (getLocalMtx, setAABB, setSphere).
#include <egg/gfxe/eggModelEx.h>

namespace EGG {

// Out-of-class (non-inline) member templates: instances are emitted after their
// first user in forward order (AABB before Sphere), as in retail.
template <typename TShape>
ModelBoundingInfo::TData<TShape>* ModelBoundingInfo::createShape(bool shapeSet) {
#line 150
    TData<TShape>* pData = new TData<TShape>();
    if (pData == NULL) {
        system_halt(lbl_803798F8 + 0x48, 151, lbl_803798F8 + 0x5f);
    }

    pData->m_pShapeSet = NULL;

    if (shapeSet) {
#line 157
        pData->m_pShapeSet = new TShape[m_pMdl->getNumShape()];
        if (pData->m_pShapeSet == NULL) {
            system_halt(lbl_803798F8 + 0x48, 158, lbl_803798F8 + 0x65);
        }
    }

    return pData;
}

template <typename TShape>
void ModelBoundingInfo::deleteShape(TData<TShape>* pData) {
    if (pData->m_pShapeSet != NULL) {
        delete[] pData->m_pShapeSet;
    }

    delete pData;
}

} // namespace EGG


#endif
