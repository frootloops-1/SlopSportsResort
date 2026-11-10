# resort: predefining a header's include guard to drop a static is unnecessary for the DOL (linker strips it)

- status: works
- tags: resort,honesty,include-guard,sdata2
- source: 2026-11-09 review

symptom: worker used #define NW4R_G3D_PLATFORM_GPU_H to drop cm2hw from .sdata2
cause: unreferenced local statics are dead-stripped at link anyway
fix: removed the define: still 27/27 and FLIP-OK; re-sync @N names afterwards (sync_local_names.py)
