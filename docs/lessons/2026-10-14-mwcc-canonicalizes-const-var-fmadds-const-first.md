# MWCC canonicalizes const*var fmadds const-first

- status: works
- tags: float,fmadds
- scope: RPGol_802adb7c
- source: fn_802AE444

symptom: fmadds operand order
cause: canonicalization
fix: inline helper taking the const as a parameter (Madd(a,b,c), AddScaledV(V3*,const V3*,float))
