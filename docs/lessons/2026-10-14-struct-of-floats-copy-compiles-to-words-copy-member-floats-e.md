# Struct-of-floats copy compiles to words; copy member floats explicitly (RPBsb_8028a088)

- status: works
- tags: struct-copy,float,loop,matching
- source: RPBsb_8028a088 (13/13 exact, DOL OK)

symptom: fn copying a 3x4 BsbMtx from a stack local into 9 member structs scores 0%: orig uses lfs/stfs f0 pairs in a bdnz loop of 9; a BsbMtx struct assignment compiles to lwz/stw word pairs unrolled x3
cause: MWCC copies a struct by integer words when assigned as a whole; the original copies each float element
fix: Assign each of the 12 floats individually inside the loop body (m->mtx.m[r][c] = mtx.m[r][c]); also an unused 2nd param (s32,) in fn_8028A234 when the caller passes idx in r5 and value in r6
