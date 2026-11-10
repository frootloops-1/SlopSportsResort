# fn_802CB278: replace extern char[] string blob + offsets with real string literals (61.5 -> 100)

- status: works
- tags: string-pool,literals,callee-saved,rodata,RPBox_802ca890
- scope: RPBox_802ca890

symptom: Retail hoists the string-pool base lis/addi into a callee-saved reg before the first call and keeps 4 callee-saved regs; extern char lbl[N] + 0xE/0x29 with inline helper, local base, member inline all stay at 61.5
cause: The dtk lumped lbl_ was really @stringBase0 pooled literals; indexing a char array does not produce the pooled-literal base CSE
fix: Use the literals directly (Load...("MainGame.carc"), BoxCommonFile("Effect/sports_boxing.breff")), delete the array def/extern; MainGame.carc must be the first literal in the TU. Try literals whenever a function indexes a lumped rodata string blob.
