# Hermite products: k * t * t spelling with literals matches retail fmuls X,X,t

- status: works
- tags: mwcc,operand-order,hermite
- scope: Pack/RPUtility/RPUtl_801C67B8
- source: claude/rputl-c67b8-1027

symptom: fmuls t,X vs retail X,t in hermite basis; every spelling failed while 2.0/3.0 were extern const lbl loads
cause: with literal constants the canonical operand order differs
fix: h0 = 1.0f + (t * (2.0f * t * t) - 3.0f * t * t); h1 = t * (-2.0f * t * t) + 3.0f * t * t; h2 = t + (t * (t * t) - 2.0f * t * t) -> fn_801C67B8 exact
