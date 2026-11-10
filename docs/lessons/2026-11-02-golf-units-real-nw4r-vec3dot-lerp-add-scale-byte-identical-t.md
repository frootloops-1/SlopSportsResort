# Golf units: real nw4r VEC3Dot/Lerp/Add/Scale byte-identical to local asm copies

- status: works
- tags: nw4r,vec3,asm,golf
- scope: Pack/RPSports/RPGolScene
- source: opus pass 4

symptom: local asm copies of VEC3 helpers (VecDot, golVecLerp, golVecAdd, golVecScale)
cause: they are nw4r::math inlines
fix: #include <nw4r/math.h> (drop the local FrSqrt decl) and call nw4r::math::VEC3Dot etc. with casts; RPGol_802c58d4 stayed 8/8 exact
