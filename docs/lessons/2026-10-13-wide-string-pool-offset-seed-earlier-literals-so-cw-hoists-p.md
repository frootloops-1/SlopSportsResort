# Wide-string pool offset: seed earlier literals so CW hoists pool base

- status: works
- tags: string-pool,wchar,hoist
- scope: RPSportsCommon_unsplit

symptom: li r5,sym per use vs original li r31,poolbase; addi r5,r31,0x38
cause: %d literal at pool offset 0 vs 0x38
fix: define the preceding literals (L"20-"..L"80-" array) earlier in the TU; remove once their owning function is written
