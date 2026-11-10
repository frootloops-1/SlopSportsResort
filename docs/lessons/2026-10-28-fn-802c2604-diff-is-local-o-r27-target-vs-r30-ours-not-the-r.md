# fn_802C2604 diff is local o (r27 target vs r30 ours), not the r29/r27 pair

- status: fails
- tags: regalloc,RPGol_802c16a4,fn_802C2604
- source: claude/gol1-1028 worker 2026-10-28

symptom: 99.82%, 3 wrong insns: lwz, mr r3, lwz r28,0xbc; target puts o (lbl_804BF948 object) in r27, ours r30
cause: ours shares r30 between o and first so they never interfere; target needs o live past first's definition
fix: no gain: block-scoped i; static inline for rec stores; golFirst() wrapper; first as u32 (99.3); golRecOf(o) (99.0). Only untried: re-read o after the first call (needs MATCH-PENDING R17 + ledger row). Park.
