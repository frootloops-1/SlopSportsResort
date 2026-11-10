# Identical store runs in both if/else arms get tail-merged

- status: works
- tags: codegen,tailmerge

symptom: six byte clears emitted once after the if
cause: MWCC merges identical arm tails
fix: write the stores inside each arm (fn_801E1708)
