# F1 strings: when ours shows @stringBase0, merge target string lbl_ symbols into one symbol NAMED @stringBase0

- status: works
- tags: F1,symbols,strings
- scope: RPSports_801E7EB4,RPUtlLytFrameCursor
- source: claude/nm-data

symptom: target lis/addi lbl_X + large addi lbl_Y+off; ours @stringBase0
cause: per-string target symbols vs compiler string pool
fix: one symbol named @stringBase0 scope:local data:string_table, size = real string bytes; RPSports_801E7EB4 4 fns. If the source DEFINES strings as separate arrays (16-byte stride) define ONE const char[] instead (RPUtlLytFrameCursor)
