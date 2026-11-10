# Trailing "" in .rodata string pool with no user

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBsbScene/RPBsb_8025ff94

symptom: Trailing "" in .rodata string pool with no user
cause: Trailing "" in .rodata string pool with no user
fix: dead static helper returning "" as first definition in a descending deferred TU
