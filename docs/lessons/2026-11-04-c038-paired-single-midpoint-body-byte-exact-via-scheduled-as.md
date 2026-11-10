# C038: paired-single midpoint body byte-exact via scheduled asm

- status: works
- tags: C038,paired-single,inline-asm,R17,byte-proof
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b340
- source: codex-c038-match; scratch/c038/relocated-proof.json and link-comparison.json

symptom: C++ 92.9: scheduler changes midpoint sum order, pivot loads coalesce, ps_mr disappears and function is four bytes short
cause: Inline work-register type/declaration helpers still allow native scheduling and CSE; a midpoint-only scheduled helper recolours the containing function. Even whole-body scheduled asm moves the last pointer update across cmpwi.
fix: Marked whole-body asm fallback, compiler-owned frame/saves, POD scalar stack storage, literal PSQ stack displacements and two annotated raw addi encodings. Independent 1272-byte/318-instruction/15-relocation proof passes at actual source-object VA. Earlier C878/E58C proofs pass at restored original VAs too. Temporary source-unit Matching link differs in only 46 E464 bytes; restore NonMatching => DOL 0. Original C++ recovery pending.
