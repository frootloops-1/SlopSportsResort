# SpMdlSetB file table identical-arm ternary closes table-base colour

- status: works
- tags: RPSports,SpMdlSetB,regalloc,R17
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c
- source: Codex 2026-11-04; ledger 209

symptom: 99.8 percent: file table base r29 instead of r28; animation-name base correctly r29
cause: Ordinary getters, named pointer masks and larger inline boundaries propagate the constant base back to the old temporary
fix: Use (idx ? lbl_803C29F8 : lbl_803C29F8)[idx] in BOTH sprintf and nullcheck. Bytes match, MATCH-PENDING R17. asm_diff may still print local symbol suffix differences; verify.py confirms 100.
