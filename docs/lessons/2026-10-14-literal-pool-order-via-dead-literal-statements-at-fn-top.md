# Literal pool order via dead literal statements at fn top

- status: works
- tags: sdata2,pool-order,literal,fakematch
- scope: RPTns_80230904
- source: sonnet worker 2026-10-14

symptom: .sdata2 pool order differs (e.g. 50,0,double,0.008,0.02)
cause: pool order is first appearance in source
fix: dead statements 50.0f; 0.0f; 4503601774854144.0; at top of the function (fakematch; RPTns_80230904)
