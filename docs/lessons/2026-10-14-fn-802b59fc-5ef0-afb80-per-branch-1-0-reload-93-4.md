# fn_802B59FC/5EF0/AFB80 per-branch 1.0 reload (93.4)

- status: open
- tags: float,cse
- scope: RPGol_802b5638
- source: fn_802B59FC

symptom: target reloads 1.0 per else sub-block, keeps d in f5
cause: unknown; MWCC CSEs 1.0 in ours
fix: dead ends: GolMap inline (92.4), double/int args, local one, GolOne() getter, breakpoint arrays, hoisted hi local
