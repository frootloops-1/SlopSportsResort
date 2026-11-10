# fn_801FE454: inline helper for repeated SE blocks fixes CurPos slot order; ctor temp c/p slot swap remains

- status: works
- tags: stack,inline,slots,regalloc
- scope: RPSports_801fdbc0
- source: worker

symptom: CurPos v locals of four identical blocks at wrong stack offsets, name/mgr in wrong callee-saved regs; SpVec3f(CurPos c,f32) by-value temp slots 0x28/0x30 swapped
cause: inline-expansion temps are laid out below block locals in expansion order; arg (c) is expanded before the ctor param copy p so order is c,p while retail is p,c
fix: worked: static inline SpCursorSe(self,name,RPSndAudioMgr*& mgr) with function-level name and mgr (mgr by reference keeps it sharing r29 with r; local mgr in helper cost r28), CurPos vl hoisted to function top, SpPanePos helper returns the CurPos (moved tmp from 0x58 to inline region). Dead: named c vs unnamed, SpInitVec(&v,c,z), SpMk nested, ctor arg order swap, SpVec3f declared at top + assignment, SpId pass-through, p=c copy inside helper (copy-prop changes instrs)

update: the c/p swap closed with a ctor delegating to a by-value set() (see stack-slots-of-temps-follow-n-order lesson); SpPanePos removed.
