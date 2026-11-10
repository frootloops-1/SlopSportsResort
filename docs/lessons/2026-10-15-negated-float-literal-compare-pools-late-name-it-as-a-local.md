# Negated float literal compare pools late: name it as a local

- status: works
- tags: sdata2,pool,order,literal
- scope: RPTns
- source: RPTns_80220994

symptom: .sdata2 order wrong for x <= -65.0f
cause: unary-minus literal is pooled after later literals
fix: f32 lo = -65.0f; before the compare (fn_802220B0)
