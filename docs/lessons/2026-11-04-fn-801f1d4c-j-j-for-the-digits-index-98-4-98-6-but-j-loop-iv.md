# fn_801F1D4C: (j+j) for the digits index 98.4 -> 98.6 but j-loop IV order unchanged; not kept

- status: fails
- tags: iv-order,801f1d4c
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c
- source: claude/sp801f1-1104

symptom: j-loop IVs ours +0xC,+4,+8,+3 vs retail +3,+0xC,+8,+4; self r17 vs r19
cause: unknown; IV creation order
fix: failed: for(j,base+=3) 356 lines, values[i][base/3] 239, value read before the if 224 (same), j+j 214 (98.6, odd spelling, not committed)
