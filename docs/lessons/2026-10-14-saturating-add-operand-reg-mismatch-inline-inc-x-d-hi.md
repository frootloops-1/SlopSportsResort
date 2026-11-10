# Saturating add operand/reg mismatch: inline Inc(x,d,hi)

- status: works
- tags: float,inline
- scope: RPGol_802b4f2c
- source: fn_802B4F2C

symptom: fadds operand order or reg differs at 99.9
cause: plain ternary / t += d shape
fix: inline float Inc(float x,float d,float hi){ float v = x + d; return v > hi ? hi : v; }
