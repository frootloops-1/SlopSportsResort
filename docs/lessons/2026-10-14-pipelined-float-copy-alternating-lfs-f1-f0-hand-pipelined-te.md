# Pipelined float copy (alternating lfs f1/f0): hand-pipelined temps

- status: works
- tags: float,copy
- scope: RPGol_802b08a0
- source: fn_802B1408

symptom: serialized copy on f0
cause: struct/loop copy
fix: float a11,...,a0; a0=m0; a1=m1; d0=a0; a2=m2; d1=a1; ...
