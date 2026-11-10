# Multi-block ctor: reuse one u8* o declared at fn top across new/ctor blocks

- status: works
- tags: regalloc,ctor
- scope: RPGol_802aaf88
- source: fn_802AC42C

symptom: saved-reg numbering differs
cause: block-scoped temps
fix: declare u8* o once at top and reuse
