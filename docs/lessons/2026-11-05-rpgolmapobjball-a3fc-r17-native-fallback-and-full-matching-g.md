# RPGolMapObjBall A3FC: R17 native fallback and full Matching gate

- status: works
- tags: RPGolMapObjBall,R17,Matching,asm
- scope: fn_8029A3FC
- source: codex-golball-1105

symptom: fn_8029A3FC remained a register/scheduling residue after documented C++ probes.
cause: Source shape and MWCC allocation/emission residue; see retained C++ and task archive.
fix: 496 bytes, 124 instructions, one relocation. Prior >80 type/snapshot/helper attempts stalled. Removing C++ changes the global inline budget: pin fn_80299C20 out of line to prevent regression in matched A204. All 54 functions and code/data sections now 100%; full source-unit DOL 0 bytes, only three known collisions. Original C++ pending; marker ledger rows215-223.
