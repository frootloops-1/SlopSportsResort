# ef_animcurve U8 key cursor phase and earlier interp address fail gate

- status: fails
- tags: ef_animcurve,U8,coalescing,scheduling
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: 38line residue includes found-key add3/value4 vs targetshared4; final key boolean setup wrong registers.
cause: Key cursor phase shifts base to4 but values becomes3 and seed address12(base), exchanging roles. Earlier interp computation changes full dependency scheduling.
fix: key+=12; values=key; helper key[-10]:99.52437/48 vs99.52941/46, rejected. Move interp before first boolean:99.2479/142 vs99.54622/38, rejected. No marker retained; next key attempt must eliminate old-base lifetime, and final setup needs actual dependency change.
