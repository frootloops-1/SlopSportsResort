# resort: x*(1.0f/y) colours the constant f0 instead of f1; named local f32 one closes it (R17 marker)

- status: works
- tags: resort,regalloc,fpr,R17
- scope: resort
- source: RP batch 5 (2026-11-09)

symptom: Clipper::Calc 99.6, f0/f1 swap
cause: MWCC FPR order for a literal numerator
fix: f32 one = 1.0f as the numerator; recorded as MATCH-PENDING ledger #3 (an inline math helper probably existed)
