# fn_801BC854 99.4 register residue: start.y/z coloring and endDistance f9 vs f7

- status: fails
- tags: mwcc,register,RPUtlCollisionChecker,fn_801BC854,permuter
- scope: Pack/RPUtility/RPUtlCollisionChecker

symptom: remaining diff: start stores order, endDistance in f7 not f9 (rotates zero/span); 48 lines
cause: pre-scheduling interference/colour tie; not diagnosed
fix: failed: start/end assignment-order sweep (36), ctor vs field mixes, scalars-then-VEC3, distances declared at top, end-first distances, Dot inline, face-first operands, const pointers placed early, 10 min permuter (best only &span fake)
