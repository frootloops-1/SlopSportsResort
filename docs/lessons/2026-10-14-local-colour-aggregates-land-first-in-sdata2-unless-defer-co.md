# Local colour aggregates land first in .sdata2 unless defer_codegen off

- status: works
- tags: sdata2,pool-order,defer_codegen,color
- scope: RPTns_8023758c
- source: sonnet worker 2026-10-14

symptom: .sdata2 83%: colour constants emitted before floats
cause: with deferred codegen, local aggregate initialisers are emitted at parse time
fix: #pragma defer_codegen off + ascending source order (RPTns_8023758c)
