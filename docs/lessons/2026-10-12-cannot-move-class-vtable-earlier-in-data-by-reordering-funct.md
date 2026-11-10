# Cannot move class vtable earlier in .data by reordering functions

- status: fails
- tags: vtable,data,jumptable,order,template
- scope: RPGrpModelAnmImplement
- source: sonnet worker, verified 2026-10-12

symptom: Original vtable is mid-.data before later jumptables; ours is last
cause: Strong vtable of explicit specialisation emitted after all jumptables
fix: Tried: reorder defs, drop Construct, out-of-line dtor, inline on InternalGetAnmObj/SetAnmObj (right direction but gets inlined into callers; dont_inline pragma and never_inline attribute do not stop it)
