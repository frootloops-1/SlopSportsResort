# Static helper functions pool float constants at their definition

- status: works
- tags: sdata2,pool,order
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc
- source: claude-rpbox-802cb9cc-1022

symptom: inline helper constants (255.0f, s32 cvt double) pooled at first use, too late
cause: with defer_codegen off a static non-inline function is compiled where it is defined; it still gets auto-inlined
fix: make the helper static (non-inline) and place it where the constants belong; the out-of-line copy is dead code
