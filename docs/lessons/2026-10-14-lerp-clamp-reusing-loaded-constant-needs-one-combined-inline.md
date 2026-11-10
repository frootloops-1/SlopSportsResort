# Lerp+clamp reusing loaded constant needs one combined inline

- status: works
- tags: float,inline
- scope: RPGol_802a7a40
- source: fn_802A7CD8

symptom: constant reloaded for clamp
cause: separate inlines
fix: LerpClamp(lo,hi,t){ v = Lerp(lo,hi,t); clamp(v,lo,hi); }
