# fn_8024929C: struct-copy lwz pairs vs target 3-load copy (TnsVec3 cur = *target)

- status: open
- tags: schedule,struct-copy,regalloc,RPTns
- scope: Pack/RPSports/RPTnsScene/RPTns_80249284

symptom: 12-byte struct copy emits lwz,lwz,stw,stw,lwz,stw pre-RA (w1/w2 share r0); target loads w1,w2 before stw w0 (w0=r4,p34=r3,w1=r3,w2=r0). Also first block: target pointer float loads tx/ty/tz scheduled before py/pz in ours, after in target.
cause: Pre-RA DAG differs: target seems to treat target-pointer loads as not ordered after stack stores; plain struct copy, assignment copy, by-value inline helper, union int copy all give the pair form
fix: Explicit u32 loads w2,w1,w0 then stores reaches 98.7 (R17 pointer punning, not committed). Tried and flat/worse: tnsAdd/tnsSub inlines (96.0), local order swaps, &self->f50 pointer, coll getter inline, unnaming s28, moving copy earlier (96.0/96.5), version sweep flat.
