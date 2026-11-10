# Unused f32 one=1.0f,zero=0.0f at fn top fixes sdata2 order 1,0,60

- status: works
- tags: sdata2,literal-order,float
- source: RPBsb_8027383c

symptom: 99.8%: pool order 60,0,1 vs original 1,0,60
cause: literals pooled in first-use order
fix: declare unused locals one/zero first, keep literals in clamp; using locals as clamp bounds pins f30/f31 (79.6%)
