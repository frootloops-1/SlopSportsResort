# Tail-merged negate branches: name the value before negating

- status: works
- tags: branch,tailmerge,fneg
- scope: RPTns_802194f8
- source: sonnet worker 2026-10-14

symptom: v.x=-Sin(..) / v.x=Sin(..) branches merged into one stfs
cause: identical store tails are merged
fix: f32 sn = Sin(..); v.x = -sn; in the negate branch (RPTns_802194f8 fn_80219968)
