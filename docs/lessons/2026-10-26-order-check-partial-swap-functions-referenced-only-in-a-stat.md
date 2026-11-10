# order_check partial swap: functions referenced only in a static table need forward decls when moved

- status: works
- tags: order,emission,reorder_fn,rpsports
- scope: Pack/RPSports

symptom: RPSportsStaticMem emitted fn_801E7794/7798 after fn_801E7A58 (source reverse of address order); moving the two empty stubs below fn_801E779C broke the build (undefined identifier, used in a table in fn_801E780C)
cause: unit emits reverse of source; stubs defined above their user in source but target address is lower than the user
fix: reorder_fn.py moves then add plain prototypes for the moved stubs near the other forward decls; 30/30 exact, DOL 0 diff, flipped Matching
