# Duplicate local-array .rodata tables: share the per-iteration body in one inline

- status: works
- tags: rodata,inline,local-array,duplicate
- scope: RPTns_80241d88
- source: opus worker 2026-10-14

symptom: object emits two copies of local const arrays, overrunning the TU .rodata
cause: orig had one static inline (called by two fns) holding the arrays
fix: move the shared per-node body with the arrays into one static inline; keep the loops in each caller (RPTns_80241d88)
