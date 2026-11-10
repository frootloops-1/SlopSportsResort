# Normalize guard !(len < FLT_MIN) and compute sq into local before inline FSqrt

- status: works
- tags: rpgolmath,fsqrt,fcmpo,float
- scope: RPGolMath
- source: sonnet

symptom: if(len>=FLT_MIN) emits cror/bne; FSqrt(expr) spills to f30/f31
cause: compare form and inline arg re-evaluation
fix: if(!(len<FLT_MIN)); f32 sq=...; FSqrt(sq)
