# u8 wrapper calling s32 callee: bl + clrlwi

- status: works
- tags: clrlwi,tailcall
- scope: RPSportsCommon_unsplit

symptom: 27.1%: we emit tail call b, original bl + clrlwi with frame
cause: callee return type u8 allows tailcall
fix: declare callee returning s32 and keep u8 wrapper return; keep unused leading param if r3 is overwritten
