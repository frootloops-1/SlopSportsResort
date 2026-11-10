# fn_80208CA0 12-byte struct return: loads-first pattern needs a 3-arg ctor but non-POD breaks caller

- status: open
- tags: struct-copy,sret,ctor,schedule
- scope: RPSports_80208744
- source: claude nearmiss 2026-10-15

symptom: orig add r5; lwzx r4; lwz r3; lwz r0; then 3 stw to sret r15; ours interleaved lwz/stw (98.0)
cause: trivial struct copy interleaves; a user 3-arg ctor SpPair(a,b,c) gives loads-first (99.8, only a/c regs r0<->r4 swapped) but makes SpPair non-POD and regresses caller fn_802098D4 69.9->64.2
fix: failed: return arr[i] / local copy / pointer deref / field-wise local (adds stack temp) / inline make helpers / copy ctor (interleaved) / reversed-param ctor / 36 decl x assign orders of locals / explicit out-param (*out=, field-wise) - out-param also regresses fn_802098D4. Revisit when fn_802098D4 is decompiled (its orig frame is 0x70, ours 0x60: caller may really use a temp + non-POD type)
