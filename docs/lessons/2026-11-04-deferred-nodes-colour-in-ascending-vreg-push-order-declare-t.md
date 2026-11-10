# Deferred nodes colour in ascending-vreg push order: declare-then-assign to swap two locals' colours

- status: works
- tags: regalloc,declaration-order,b340,BD58
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b340

symptom: retail t2 f1, t1 f2; ours t1 f1, t2 f2
cause: deferred nodes pushed by ascending vreg; higher vreg colours first
fix: f32 t0 = ...; f32 t2; f32 t1 = ...; t2 = ...; gives t2 the higher vreg -> BD58 100
