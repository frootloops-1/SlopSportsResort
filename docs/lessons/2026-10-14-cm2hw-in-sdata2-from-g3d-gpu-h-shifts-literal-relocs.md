# cm2hw in .sdata2 from g3d_gpu.h shifts literal relocs

- status: works
- tags: sdata2,reloc,header,g3d
- scope: RPTns_8022863c
- source: opus worker 2026-10-14

symptom: reloc-only 99.x% misses; extra cm2hw entry in our .sdata2
cause: g3d_gpu.h static const pulled in through RPGrpCamera/egg includes
fix: #define NW4R_G3D_PLATFORM_GPU_H before includes (RPTns_8022863c)
