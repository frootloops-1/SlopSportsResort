# RPGolMapObjBall 974B0: scheduled asm closes copy/load wall; distinguish shifted call relocations

- status: works
- tags: R17,asm,relocations,proof,RPGolMapObjBall
- scope: fn_802974B0
- source: codex-golball-1105

symptom: 974B0 at 99.8232%: vector copy GPRs and loop-condition load order remain wrong after >70 new C++ probes and earlier type/copy variants.
cause: MWCC load-temp allocation/scheduling; ordinary declaration/load/helper/condition reshapes stalled. Even scheduling-off asm moves address-add pseudos. Remaining unit text shifts later callees +8.
fix: R17 row216 scheduled body, compiler-owned Frame/saves/epilogue; lock addi r5,r5,-2 and addi r3,r3,0x54 with annotated 0x38A5FFFE/0x38630054. 198/198 instructions and object relocs exact. Verify actual +8 call targets for 802A39BC/38E0/39E0/3DE4; retail-relocated 792/792 bytes exact, raw source-unit function has four displaced call bytes. Configured DOL0, known collisions only; full unit stays NonMatching. Use unnamed parameters to avoid unused-argument errors with asm; prior C++ retained under #if0.
