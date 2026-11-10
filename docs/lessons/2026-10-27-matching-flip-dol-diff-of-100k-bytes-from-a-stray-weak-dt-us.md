# Matching-flip DOL diff of 100k+ bytes from a stray weak __dt: use the original's type (VEC3, not Vector3f) for locals

- status: works
- tags: eggCpuTexture,link,weak,extab,flip-check
- scope: egg/gfxe/eggCpuTexture
- source: claude/cpu2-1027 sonnet

symptom: Flipping eggCpuTexture to Matching shifted all of .text by -16 (115571 differing bytes); .data/.sdata2 looked low in objdiff
cause: Local Vector3f in fillNormalMapSphere made the TU emit a weak __dt__Q23EGG8Vector3f (no extab, exceptions off) that won the link over eggDrawHelper's copy, dropping one extab+extabindex entry (8+12 bytes). The original TU emits no such dtor, so its local was nw4r::math::VEC3.
fix: Declare the local as nw4r::math::VEC3: Matching-link diff 6 bytes, all in setColor. Check nm of the .o for unexpected W __dt/@STRING@ symbols; objdiff .data % is low only from weak data the original keeps in other units.
