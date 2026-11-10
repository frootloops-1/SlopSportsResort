# fn_801F6680/fn_801F3C78: preheader addi/mr IV init scheduled before li constants (rank 2 beats rank 4 on ties)

- status: open
- tags: pre-ra-schedule,iv-init,801f1d4c,parked
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c
- source: claude/sp801f1-1104

symptom: retail 'li r27,0; li r29,0; addi r30,..vt' and 'li r27,0; mr r29,r26'; ours put the addi/mr first
cause: mwcc_sched_trace: in the preheader all candidates have height 1; the scheduler picks the rank-2 addi/mr over rank-4 li even though li comes first in the optimizer order
fix: 6680: dropping named zero/seven/vt locals for a plain for loop 97.7 -> 98.5 (2 lines left). Failed for both: do/while, i declared outside, pointer IV, inline new helpers, statement swaps, screenScale local
