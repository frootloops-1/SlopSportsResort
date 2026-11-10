# IRO CSE var stuck in pass 2: make the inline's index a named caller local (int& param)

- status: works
- tags: RPBow_80320EFC,fn_80320EFC,gpr,regalloc,model
- scope: fn_80320EFC

symptom: lerp count-1 CSE var (@681) took r31, retail r28; sim said it needs 2 fewer unremoved neighbours or a vreg above the lerp i @vars
cause: the inline-local lerp indices (@542/@551) are numbered above @681, so they are still unremoved when @681 is checked in pass 1 (31 neighbours >= 28)
fix: BowLerpTblCol7Ref(f32 x, int& i) with a named caller int i: named vars are lowest, removed first -> @681 in pass 1 -> r28 (R17 272). Helper-return/param/scoped/named last for count-1 all no change
