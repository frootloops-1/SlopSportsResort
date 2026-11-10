# Single-case switch emitting an extra bge needs an empty neighbour case

- status: works
- tags: switch
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc
- source: claude-rpbox-802cb9cc-1022

symptom: target cmpwi 7; beq; bge end; b end - ours had no bge
cause: the original switch had another empty case below the real one
fix: add case 6: break; (case 8 or default did not work)
