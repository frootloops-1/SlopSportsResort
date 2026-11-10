# dont_inline pragma also blocks inlining inside the wrapped bodies

- status: works
- tags: inline,pragma,rpbsb
- source: RPBsb_80283fe0 2026-10-16

symptom: callee bodies start calling SetNearZ/ctors
cause: #pragma dont_inline applies to calls inside the region
fix: wrap the callers, not the callees
