# ef_animcurve Texture in-place float value and inline scale boundary fail FPR colour gate

- status: fails
- tags: ef_animcurve,Texture,FPR,coalescing
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Texture99.97319 leaves conversion f0 vs targetf1 before multiply resultf1.
cause: Arithmetic source/dest lacks copy edge; named in-place frameValue or inline mutable value coalesces conversion and multiply into f2 but magic constant becomesf1, target reverse.
fix: frameValue after loop, same bare decl hoisted to function top, inferred inline ScaleFrameValue mutable parameter all99.906166/10lines vs99.97319/4. Reverted/no helper retained. Actual fpr graph in texture-n-value. Park after no-gain bound; need causal way to make anonymous coalesced product takef1.
