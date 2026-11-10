# h+(h-b)*t*t*(2t-3) blend is the CubicEase inline from RPGolUtlVec.cpp

- status: works
- tags: float,inline
- scope: RPGol_802b4f2c
- source: fn_802B4F2C

symptom: blend arithmetic shape
cause: shared inline
fix: copy CubicEase inline locally
