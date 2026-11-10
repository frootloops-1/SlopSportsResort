# Header-pooled unused statics land in the TU: define header guards

- status: works
- tags: sdata2,header,guard,cm2hw,dead-strip
- scope: RPGrpModelAnmImplement
- source: sonnet worker, verified 2026-10-12

symptom: Extra 4-byte items in .sdata2 shift float constants
cause: g3d_gpu.h cm2hw and eggPostEffectBlur.h float get emitted though unused (orig dead-stripped)
fix: #define NW4R_G3D_PLATFORM_GPU_H / EGG_GFXE_POST_EFFECT_BLUR_H before includes (hack; commented)
