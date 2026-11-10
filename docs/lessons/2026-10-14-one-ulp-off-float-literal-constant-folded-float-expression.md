# One-ulp-off float literal = constant-folded float expression

- status: works
- tags: float,literal,sdata2,fold
- scope: RPTns_80219d24
- source: claude 2026-10-14

symptom: .sdata2 98%: literal 0x3FEE147A vs ours 1.86f (0x3FEE147B)
cause: source wrote (5.0f - 3.14f), folded in single precision
fix: find a nearby literal pair whose float difference/product gives the exact bits (fn_8021A3BC)
