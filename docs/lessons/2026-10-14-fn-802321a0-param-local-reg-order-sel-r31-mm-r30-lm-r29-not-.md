# fn_802321A0 param/local reg order (sel r31 mm r30 lm r29) not reproduced

- status: fails
- tags: regalloc,params
- scope: RPTns_802318a4
- source: claude/rptns-2

symptom: orig sel=r31 mm=r30 lm=r29 self=r28; ours mm=r31 lm=r30 sel=r29 self=r28 (93.8%)
cause: unknown coloring-priority difference
fix: tried temp i=sel, ternary, nested if, TnsFile* pointer, mm hoisted before the if, sel typed u8/u16/s16/u32: no change
