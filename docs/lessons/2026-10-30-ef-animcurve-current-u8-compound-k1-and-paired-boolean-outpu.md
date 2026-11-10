# ef_animcurve current U8 compound k1 and paired boolean output refs canonicalize flat

- status: fails
- tags: ef_animcurve,U8,coalescing,inline,tail
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Current-main U8 is 99.58403 with 20 changed lines. The model requires both generated neg/or temporaries to have older identities.
cause: Compound k1 construction and explicit paired boolean output references do not change emitted allocation. No rejected-candidate graph was captured.
fix: Both k1=keys; k1+=(idx+1)*keySize and CurveFlagSet(flag,negative,combined) with outputs declared after bare k1 produce identical code. The helper returns the signed OR value <0. Both trials were reverted after the two-no-gain bound; no helper or marker retained. Tail residue remains colouring exposed by post-RA scheduling. Source-level preservation of the modeled identities remains unresolved.
