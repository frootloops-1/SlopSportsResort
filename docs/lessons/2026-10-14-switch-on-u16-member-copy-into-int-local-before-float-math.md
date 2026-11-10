# Switch on u16 member: copy into int local before float math

- status: works
- tags: switch,lhz,scheduling
- scope: RPTns_80224cf8
- source: opus worker 2026-10-14

symptom: lhz index in r0 after mfcr instead of r3 before fcmpo
cause: member read point
fix: int k = it.idx; before the float code, switch(k) (fn_80224E7C)
