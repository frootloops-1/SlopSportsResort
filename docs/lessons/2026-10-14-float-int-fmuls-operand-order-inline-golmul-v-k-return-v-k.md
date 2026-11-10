# float*int fmuls operand order: inline GolMul(v,k){return v*k;}

- status: works
- tags: float,fmuls
- scope: RPGol_802a7a40
- source: fn_802A7C74

symptom: fmuls operands swapped
cause: canonicalization
fix: inline GolMul(float v, float k){ return v*k; }
