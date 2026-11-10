# TRK hoisted 4-aligned string pool via rodata struct + local pointer

- status: works
- tags: trk,metrotrk,string-pool,rodata,hoist
- scope: MetroTRK

symptom: TRKDoSetOption orig lis/addi r31 pool base at entry, strings at 0/0x20/0x28; literals give per-use lis/addi and packed 0/0x1f/0x27 (80.1)
cause: string pool base hoisted by original compiler; GC/2.7 does not for literals
fix: static const struct {char a[0x20]; char b[8]; char c[0x10];} in .rodata + const T* strs = &obj at fn top -> 98.8 and .rodata 100. Residual: orig addi r3,r31,0 for first string, ours mr r3,r31 (+0, &x[0], (u32)+off, char* base all fold); pool_data pragma with 3 arrays: 84.2
