# Transposed 3x4 copy: loads descending, stores ascending -> inline 12-float ctor

- status: works
- tags: matrix,ordering
- scope: RPGol_802b7df8
- source: fn_802B7F10

symptom: store order follows source order
cause: MWCC evaluates ctor args right to left
fix: struct M34{float m[12]; M34(float a,...){m[0]=a;...}}; M34 o(src[0],src[3],...)
