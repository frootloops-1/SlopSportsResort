# remap inline: 'float d = in1; d -= in0;' prevents constant folding with orig register

- status: works
- tags: float,inline
- scope: RPGol_802b020c
- source: fn_802B03B8

symptom: 30-0 folded / wrong reg
cause: MWCC folds hi-lo of constants
fix: float d = in1; d -= in0; (not d = hi - in0; not const-ref params)
