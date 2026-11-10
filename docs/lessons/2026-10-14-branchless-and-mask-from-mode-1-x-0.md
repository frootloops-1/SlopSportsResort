# Branchless and-mask from mode==1 ? x : 0

- status: works
- tags: branchless,ternary
- scope: RPTns_8022a17c

symptom: subi/subfic/nor/srawi/and sequence
cause: -
fix: write flag = mode == 1 ? x : 0
