# Pool literal order equals emission order; named const objects and dead-stripped functions reorder it

- status: works
- tags: sdata2,pool,order,marker
- scope: RPUtl_801C72A0,RPUtl_801C734C,RPUtl_801C73B0
- source: claude/rputl-c67b8-1027

symptom: retail pool order differs from .text order in a split TU
cause: deferred and defer_codegen-off modes both pool literals in emission order; named extern const objects precede the pool; constants of an unreferenced function stay pooled after mwld dead-strips it
fix: named extern const for the first constant, or an unreferenced function placed to codegen first (desc source: at the end); both marked R17; DOL trial link confirmed the dead function is stripped
