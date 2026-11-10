# Hand-expanded sound sequence -> member inline startSystemSeWithRemote(literal, flag) closes r28-r30 rotation (RPSports_801ee354 3 fns 98.7-98.9 -> 100)

- status: works
- tags: inline-member,regalloc,string-pool,defer,RPSports_801ee354
- scope: RPSports_801ee354

symptom: three fns 98.7-98.9, .rodata 0%, .sdata2 50%
cause: hand-expanded RPSndAudioMgr spInstance/changeNameToIdRP/setRemote sequence; extern string blob and sdata2 externs
fix: Call the member inline startSystemSeWithRemote("...", flag); literals; sdata2 externs -> literals; descending order. Dead leading pool strings: use non-const 'const char* X[]' (goes to .data) not 'const char* const' (lands in .rodata before @stringBase0). R17 ledger 105.
