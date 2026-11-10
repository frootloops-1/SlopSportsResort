# double beq in dtor from intermediate base with inline virtual dtor

- status: works
- tags: dtor,beq,inline,RP_DEBUG_STUB_1,emission-order
- scope: Pack/RPSports/RPBowScene/RPBowMotionBlur
- source: claude/nm-3 2026-10-16

symptom: Derived dtor of RP_DEBUG_STUB_1 subclass: target has 'beq L0; beq L1' (two null checks) around the base __dt__ call, ours one
cause: Original hierarchy has an intermediate class whose dtor is inline; inlining its __dt__ adds a nested if(this)
fix: Insert 'class XBase : public RP_DEBUG_STUB_1 { public: virtual ~XBase() {} };' between them (no layout change). RPBowMotionBlur also needed fn_8034D4F0 placed before the dtor in source for DOL order
