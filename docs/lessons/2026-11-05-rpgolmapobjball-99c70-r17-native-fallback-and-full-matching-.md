# RPGolMapObjBall 99C70: R17 native fallback and full Matching gate

- status: works
- tags: RPGolMapObjBall,R17,Matching,asm
- scope: fn_80299C70
- source: codex-golball-1105

symptom: fn_80299C70 remained a register/scheduling residue after documented C++ probes.
cause: Source shape and MWCC allocation/emission residue; see retained C++ and task archive.
fix: 968 bytes, 242 instructions, 25 relocations. Exact global reload and vector FP ordering close the previous -4-byte residue; C++ vector constructor probes stalled. All 54 functions and code/data sections now 100%; full source-unit DOL 0 bytes, only three known collisions. Original C++ pending; marker ledger rows215-223.
