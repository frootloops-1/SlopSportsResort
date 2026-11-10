# ef_animcurve U8 rvalue reference moves range size into earlier simplify wave

- status: works
- tags: ef_animcurve,U8,register-allocation,reference,graph
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: U8 98.52521, 494 normalized +/- diff lines; rangeSize82 in same late simplify wave as parameter clique.
cause: Const scalar reference retains an early dominating anonymous rvalue (v671); it simplifies earlier and colours after parameters, unlike the named rangeSize.
fix: Keep const u32& rangeSize=count*2 at original site and move execution mask copy after hiFrame. U8 98.768906/382 lines, exact opcode counts; table/loop/hi/mask all target colours. R17+ledger required. Remaining displacement is nextLoop61 r25 vs target20, not early flags (which only reuses r25). DOL0, .sdata2 100; not a full match.
