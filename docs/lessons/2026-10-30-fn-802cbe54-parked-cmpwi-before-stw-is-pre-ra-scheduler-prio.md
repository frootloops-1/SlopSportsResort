# fn_802CBE54 parked: cmpwi-before-stw is pre-RA scheduler priority, BoxToScreen slot swap source-flat

- status: fails
- tags: schedule,stack-slot,inline,return-temp
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc
- source: claude-op-cb9cc-20261031

symptom: 98.3: cmpwi kind scheduled before stw 0x78; inline v at 0x8 / return copy at 0x10 (target 0x10 / 0x8)
cause: mwcc_dbg: IR order is lwz, li, stw, cmpi (target order); the pre-RA scheduler (backend-01 -> 02) lifts cmpi above stw. Slot order: the copy destination is older than the inline's v in our build
fix: failed (all identical 18-line diff or worse): load kind after the store (lwz r0, 98.2), v declared before out, aggregate v, rec.pos = BoxToScreen(), const BoxVec2& v, nested BoxXY inline, BoxSetPos(rec, BoxVec2 p) and const& p, ctor-bearing BoxScr type (frame +8), caller v declared up front + assignment (94.6)
