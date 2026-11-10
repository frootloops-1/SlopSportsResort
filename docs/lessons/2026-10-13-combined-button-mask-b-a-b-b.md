# Combined button mask: (b&A)|(b&B)

- status: works
- tags: rlwinm,rlwimi
- scope: RPSportsCommon_unsplit

symptom: rlwinm+rlwimi. pattern
cause: bitwise or of masked tests
fix: ((b & A) | (b & B)) instead of || 
