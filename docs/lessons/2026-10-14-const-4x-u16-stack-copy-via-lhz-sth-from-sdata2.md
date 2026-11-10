# const 4x u16 stack copy via lhz/sth from sdata2

- status: works
- tags: sdata2,struct-copy
- scope: RPGol_802b1a0c
- source: fn_802B240C

symptom: li/sth instead of lhz/sth
cause: field-wise assignment
fix: static const S16 k = {...}; S16 col = k;
