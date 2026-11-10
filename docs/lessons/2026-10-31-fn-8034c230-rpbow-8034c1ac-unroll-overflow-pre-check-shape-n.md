# fn_8034C230 (RPBow_8034C1AC): unroll overflow pre-check shape not steerable by loop-bound spelling (99.1%)

- status: fails
- tags: rpbow,8034c230,unroll,loop,nogain
- source: worker flip-b1ac 2026-10-31

symptom: 99.1%; only diff is the unrolled sum-loop preheader 0x8034C3B8-0x8034C418: original computes n+3 and n+2 separately from a reloaded field_20, ours CSEs n+3 then subi 1; regs shift r8/r9, r4/r7
cause: unknown; maybe differently typed field_20 or a shared inline in another header (needs shared-type change)
fix: dead: field_20+1+2, 3+field_20, reversed compare, local n (97.0), i<n+4 (92.9), do-while (93.6), i=0 form (86.4), fused && (73.4), rows ternary/local (93.5-96.1), static inline const-ptr helper (97.8), i-3<=n (73.6). Untried: retype BowSceneState::field_20 or shared inline.
