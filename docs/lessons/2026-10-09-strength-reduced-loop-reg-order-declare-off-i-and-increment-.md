# Strength-reduced loop reg order: declare 'off, i' and increment off first

- status: works
- tags: RPGolFieldManager,loop,regalloc

symptom: offset/counter registers swapped in for(s32 i...) loop
cause: CW pairs regs by declaration/increment order
fix: s32 off,i; for(i=0,off=0;cond;off+=stride,i++) matching asm addi order (helped but did not fully close 80293978/3B90)
