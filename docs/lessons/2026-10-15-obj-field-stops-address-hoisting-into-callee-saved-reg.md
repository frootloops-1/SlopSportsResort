# &obj->field stops address hoisting into callee-saved reg

- status: works
- tags: addressing,loop,regalloc
- scope: RPTns
- source: RPTns_80220994

symptom: obj+8 hoisted into r31 before loop
cause: (T*)((u8*)obj+8) cast form
fix: use &obj->field (fn_80221D74/F20)
