# fn_801FC7F8 add chain: c + 50 + rand reassociates into r3 temp

- status: works
- tags: fn_801FC7F8,regalloc,reassociation
- scope: RPSports_801fc7f8
- source: claude/x-fc7f8-1029

symptom: target add r3,r26,r3; addi r27,r3,0x32; ours add r27,r26,r3; addi r27,r27,0x32
cause: c + rand + 50 evaluates directly into b; with the constant first (c + 50 + rand) MWCC reassociates the +50 to the end and the inner add gets a fresh temp
fix: write b = c + 50 + fn_801BEBC0(100); (c + (rand+50)) and rand+50+c flip add operands). 16 -> 12 diff lines
