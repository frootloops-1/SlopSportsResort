# Branchless (n>=0)?(1<<n):0 mask is a ternary

- status: works
- tags: ternary,mask,branchless
- scope: RPTns_80248bb8
- source: sonnet worker 2026-10-14

symptom: srwi r3,r4,31; slw; subi; and with wrong regs from bitwise forms
cause: source was a ternary
fix: (n >= 0) ? (1 << n) : 0 (fn_80248BB8)
