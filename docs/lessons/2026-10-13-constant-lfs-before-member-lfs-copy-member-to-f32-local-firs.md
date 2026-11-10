# Constant lfs before member lfs: copy member to f32 local first

- status: works
- tags: mwcc,float,scheduling
- source: RPGol_802b90b4

symptom: lfs pair order swapped (literal loaded before member)
cause: expression shape
fix: f32 v = m.m[0]; (int)(v * 80.0f); fmuls operand order still differs and 80.0f*v vs v*80.0f is canonicalised
