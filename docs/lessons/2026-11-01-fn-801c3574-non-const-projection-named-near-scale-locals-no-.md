# fn_801C3574: non-const projection, named near/scale locals, no scaleLength helper

- status: works
- tags: constness,fn_801C3574,fpr,colouring,RPUtility
- scope: Pack/RPUtility/RPUtlLytBase
- source: constsweep 2026-11-01

symptom: 98.7%; schedule identical after removing const on projection, only FPR colours differ
cause: FPR colouring is descending vreg: -near must be a backend fneg created after the 0.0f load, 1.0f/y named locals coloured late
fix: f32 near = projection->distance; f32 scale = 1.0f; y = scale*(near*heightRatio); -near inline in the Vector3f ctors; const on projection drops to 97.9; unit also needs the NW4R_G3D_PLATFORM_GPU_H include-guard predefine for the cm2hw .sdata2 leak
