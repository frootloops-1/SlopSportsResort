# __ct__5TnsPl closed: player-first inline local + shadow pointer as early-created inline local

- status: works
- tags: RPTnsScene,regalloc,inline,vreg-order,mwcc_dbg,MATCH-PENDING
- source: claude/tns-ctor-1103

symptom: TnsPl ctor 99.8: TnsSndObj loop i/player swapped (r25/r26) and new TnsShadow pointer r25 instead of r27
cause: mwcc_dbg + colour replay (scratch sim of color_sim model): target needs vreg order player < b < i < shadow. vregs are numbered in reverse @ creation order; an inline's locals are created at expansion start in reverse declaration order (params first); coalesced webs take the lowest (latest) member, so a named local assigned from a new-expression still gets the new temp's late number
fix: TnsSndObj as one no-arg inline ctor declaring 'SoundArchivePlayer& player = <global expr>; u8* b; int i;' (player created last) -> 99.9; shadow: invented inline member InitHead (ctor body through SetTexture) with top-declared 'TnsShadow* shadow' set by operator new(sizeof) + placement new (no new-expr temp) -> 100, unit flipped. Dead ends: TRPSndObject-style extra (mgr, flag) params, templates, out-of-class/after-caller inline ctor, static non-inline new helper (inlined but also emitted), real-class chain views (b folded into r31 offsets), named outer local shadow (r23), 'if (shadow) new (shadow)' (extra beq)
