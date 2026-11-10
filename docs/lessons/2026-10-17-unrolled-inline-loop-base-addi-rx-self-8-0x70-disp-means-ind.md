# Unrolled-inline loop base addi rX,self,8 + 0x70 disp means index var starts at 2

- status: works
- tags: loop,strength-reduction,regalloc,inline
- source: RPBsb_80263eec 2026-10-17

symptom: orig addi r5,r3,0x8 then lwz 0x70(r5); ours mr r6,r3 + 0x78; regs rotated (fn_80263EEC 93.2)
cause: source indexed array1[i+2] with i from 0; orig loops i=2..5 with separate counter j for the stored value, id read into a local first
fix: for (s32 j=0,i=2;i<6;j++,i++){ s32 id=arr[i]; Find(self,id)->f=j; } (increment order j++,i++ fixes addi order)
