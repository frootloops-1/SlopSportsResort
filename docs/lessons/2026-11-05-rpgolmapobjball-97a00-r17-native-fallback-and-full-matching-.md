# RPGolMapObjBall 97A00: R17 native fallback and full Matching gate

- status: works
- tags: RPGolMapObjBall,R17,Matching,asm
- scope: fn_80297A00
- source: codex-golball-1105

symptom: fn_80297A00 remained a register/scheduling residue after documented C++ probes.
cause: Source shape and MWCC allocation/emission residue; see retained C++ and task archive.
fix: 2908 bytes, 727 instructions, 107 text relocations. Recover its original 17-entry .data jump table explicitly as function+case-offset pointer relocations, before vtables; rename @14898 to inferred GolBallCollisionDispatch. Direct SDK math linker names need declarations. All 54 functions and code/data sections now 100%; full source-unit DOL 0 bytes, only three known collisions. Original C++ pending; marker ledger rows215-223.
