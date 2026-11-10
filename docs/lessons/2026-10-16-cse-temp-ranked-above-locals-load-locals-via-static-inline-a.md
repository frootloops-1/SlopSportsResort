# CSE temp ranked above locals: load locals via static inline accessors

- status: works
- tags: regalloc,inline,nonvolatile,rpbsb
- scope: RPBsb_8028aef0
- source: claude/rpbsb-3

symptom: cur*4 CSE temp gets r30 vs r27, other locals shifted
cause: MWCC colors temps first, then locals in decl order, then params; inlined accessor results rank like earlier temps
fix: Read struct fields via small static inline accessors (all three needed in fn_8028AFB4). Don't wrap whole body in inline (auto-inlines into caller).
