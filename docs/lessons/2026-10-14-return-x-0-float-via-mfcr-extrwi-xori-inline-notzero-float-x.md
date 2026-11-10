# return x!=0 float via mfcr/extrwi/xori: inline notZero(float x){float z=0.0f; return z != x;}

- status: works
- tags: float,compare
- scope: RPGol_802b020c
- source: fn_802B03B8

symptom: cntlzw or extrwi shape mismatch
cause: comparison operand order
fix: bool notZero(float x){ float z=0.0f; return z != x; }
