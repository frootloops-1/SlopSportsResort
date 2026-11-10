# RPGolMapObjBall 98E70: R17 native fallback and full Matching gate

- status: works
- tags: RPGolMapObjBall,R17,Matching,asm
- scope: fn_80298E70
- source: codex-golball-1105

symptom: fn_80298E70 remained a register/scheduling residue after documented C++ probes.
cause: Source shape and MWCC allocation/emission residue; see retained C++ and task archive.
fix: 1720 bytes, 430 instructions, 42 relocations; explicit 0xA0 frame and two 0x3884000C basis-pointer updates. C++ cached-pointer/dot-local probes stalled; compiler-owned epilogue moved LR. Native nofralloc closes it. All 54 functions and code/data sections now 100%; full source-unit DOL 0 bytes, only three known collisions. Original C++ pending; marker ledger rows215-223.
