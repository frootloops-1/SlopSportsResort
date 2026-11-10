# Compiler-version sweep: SDK units may need an older mwcc build (pf_cp932 matched on GC/3.0a5)

- status: works
- tags: mw_version,compiler-version,scheduler,pf_cp932,sdk
- source: da684d4c3

symptom: Scheduler/regalloc walls in Nov-2006 SDK code (li r3,1 hoisted, temp in r5) that no source spelling fixes
cause: 3.0a5.2's pre-RA scheduler differs from 3.0a5/3.0a3.x. pf_cp932 OEM2Unicode is exact unmodified on 3.0a5; Unicode2OEM then needs the u16 temp (same extra local as the newer-SDK reference decomp). configure.py already supports per-object mw_version (NdevExi2AD uses GC/3.0a3).
fix: Before any variant search on an SDK (revolution/*) unit below 100%, compile it with every compiler in build/compilers/GC (3.0a5, 3.0a3.4/.3/.2, 3.0a3) via the ninja command with the path swapped and compare asm_diff. Set Object(..., mw_version="GC/3.0a5"). Debugger: compare backend-01 vs backend-02 to confirm a scheduler effect.
