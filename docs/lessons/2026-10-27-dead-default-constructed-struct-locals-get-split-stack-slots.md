# Dead default-constructed struct locals get split stack slots

- status: works
- tags: mwcc,dead-store,frame
- source: RPUtl_801C9E7C

symptom: 4 hoisted single 0.0f stfs to scattered stack offsets at function top
cause: 2 unused locals whose 2-float ctor stores were scalarised into separate slots
fix: Descriptor d1, d2; at function scope (MATCH-PENDING marker)
