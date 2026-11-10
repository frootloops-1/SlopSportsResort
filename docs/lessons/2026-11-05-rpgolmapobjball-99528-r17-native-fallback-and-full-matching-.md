# RPGolMapObjBall 99528: R17 native fallback and full Matching gate

- status: works
- tags: RPGolMapObjBall,R17,Matching,asm
- scope: fn_80299528
- source: codex-golball-1105

symptom: fn_80299528 remained a register/scheduling residue after documented C++ probes.
cause: Source shape and MWCC allocation/emission residue; see retained C++ and task archive.
fix: 872 bytes, 218 instructions, 23 relocations. Preserve SDK helper tail b, not bl, and declare existing GPR helper symbols for native assembly. Earlier vector/word-copy probes stalled. All 54 functions and code/data sections now 100%; full source-unit DOL 0 bytes, only three known collisions. Original C++ pending; marker ledger rows215-223.
