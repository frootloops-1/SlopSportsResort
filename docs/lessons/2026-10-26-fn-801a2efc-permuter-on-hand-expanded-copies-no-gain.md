# fn_801A2EFC permuter on hand-expanded copies: no gain

- status: fails
- tags: fn-801a2efc,RPSysSystemWinMgr,permuter
- source: claude 2026-10-26

symptom: permuter -j6 15 min ~6000 iters with the 4 UpdateButtonAnm copies expanded inline in the target (verify 98.7, permuter base score 940)
cause: no candidate beat base; ~22k permuter failures and 1.3k compile errors, so most mutations die on this stand-in
fix: unsolved; setup needs --name fn_801A2EFC --static for free-function names. Next: manual search for the extra coalesced GPR node
