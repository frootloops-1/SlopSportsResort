# RPGolMapObjBall 99890: prefix helpers fix stack but GPR swap needs R17 fallback

- status: works
- tags: R17,asm,GPR,stack,relocation-proof,RPGolMapObjBall
- scope: fn_80299890
- source: codex-golball-1105

symptom: 99890 98.3357%, hit/self registers swapped and point/copy slots reversed; new C++ helper/type probes stall.
cause: Inline prefix helper plus amount/kind declaration reversal fixes vector slots but hit/self allocation remains r29/r31. Flag-local permutations, s32/u32/s64/u64 hit types and explicit first-call flag argument remain flat.
fix: R17 row217 scheduled body, compiler-owned Frame {kind,amount,point,copy}; scheduling on for initial li31/mr30/mr29 interleaves saves, off thereafter. 143 instructions, 572 raw object bytes and 18 relocations equal original; no opwords. Source-linked function base +12, 10 call bytes differ solely from layout; verify actual targets and retail-relocate to get 572/572 bytes. Configured DOL0, known collisions only, unit remains NonMatching; earlier C++ retained. Original r4 flag survives first call setup despite previous one-arg C cast.
