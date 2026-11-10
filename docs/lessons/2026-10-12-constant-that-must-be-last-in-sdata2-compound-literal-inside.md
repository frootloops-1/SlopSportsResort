# Constant that must be last in .sdata2: compound literal inside function, not file-scope const

- status: works
- tags: sdata2,pool,order,compound-literal,GXColor,const
- scope: RPGrpView
- source: sonnet worker, verified 2026-10-12

symptom: file-scope static const / extern const is emitted at parse time so it lands first in .sdata2; target has it after codegen-time float literals
cause: Named const objects are emitted at parse; pooled literals follow codegen/text order
fix: Use mClearColor((GXColor){0,0,0,255}) in the ctor init list
