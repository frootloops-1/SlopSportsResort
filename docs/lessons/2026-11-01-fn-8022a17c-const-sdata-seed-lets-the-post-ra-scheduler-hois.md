# fn_8022A17C: const .sdata seed lets the post-RA scheduler hoist its load above prologue stores

- status: works
- tags: const,sdata,post-ra,prologue,fn_8022A17C,R17,RPTns
- scope: Pack/RPSports/RPTnsScene/RPTns_8022a17c
- source: wave3 2026-11-01

symptom: 92.4%: seed lwz after stw r30 in ours, before stw r31 in the target; rest of the LCG schedule identical
cause: prologue stores have no object attached; only a const-qualified object load escapes the dependency; diagnostic: backend-06-after-peephole matches target order but final code differs around the prologue stores = post-RA memory dependencies (constness), not source order
fix: extern const u32 seed + end-of-file __declspec(section .sdata) const definition + *(u32*)& store (R17 row 67); a (const u32*)& use-site cast changes nothing; natural u16 r = rand16()>>14 form 89.3
