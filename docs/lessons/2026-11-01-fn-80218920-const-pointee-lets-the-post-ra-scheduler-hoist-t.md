# fn_80218920: const pointee lets the post-RA scheduler hoist the param load above prologue stores

- status: works
- tags: const,post-ra,prologue,fn_80218920,RPTns
- scope: Pack/RPSports/RPTnsScene/RPTns_80216810
- source: wave3 2026-11-01

symptom: 84.7%: target's lfs f1,0(r4) sits above prologue stw r0/stw r31; ours after mr r31,r4 (recorded 2026-10-15 'prologue lfs f1 hoist', 15 forms tried)
cause: post-RA scheduler hoists a load above stack stores only when it can prove no alias; a const-pointee load counts as safe, plain f32* does not
fix: int fn_80218920(TnsZ* self, const f32* p) with literals 30.0f/-30.0f; dead f32** pp and lbl externs removed (no effect on the schedule). No marker. Check pointee constness FIRST on any param-load-above-prologue-stores wall
