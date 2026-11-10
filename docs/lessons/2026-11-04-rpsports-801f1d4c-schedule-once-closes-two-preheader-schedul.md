# RPSports 801f1d4c schedule once closes two preheader scheduling walls

- status: works
- tags: RPSports,scheduling,R17,fn_801F3C78,fn_801F6680
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c
- source: Codex 2026-11-04; ledger 210-211

symptom: Only li-zero versus mr/addi ordering differs; ordinary source changes all flat
cause: Pre-allocation scheduler prefers rank-2 copies/address additions over rank-4 constants; source declaration moves cannot defeat that tie
fix: Local pragma schedule once, followed by schedule reset, closes BOTH functions; verify 70/74 no regressions, all data sections 100. R17 because real inline shape remains unresolved.
