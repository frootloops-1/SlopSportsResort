# Pool order: named extern const objects always precede compiler literals

- status: works
- tags: mwcc,pool,sdata2
- source: RPUtl_801C9E7C

symptom: target sdata2 has lbl_ named floats after @ literals
cause: user-defined const objects are emitted before deferred-codegen literals, even when defined at TU end
fix: use literals and seed creation order with dead literal statements (0.0f; 4503599627370496.0; in first-generated fn, 1.0f; in sinit) - MATCH-PENDING
