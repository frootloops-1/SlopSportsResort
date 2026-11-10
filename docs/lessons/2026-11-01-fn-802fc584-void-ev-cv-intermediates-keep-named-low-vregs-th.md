# fn_802FC584: void* ev/cv intermediates keep named low vregs through copy-prop

- status: works
- tags: copy-propagation,vreg,fn_802FC584,R17,RPBox
- scope: Pack/RPSports/RPBoxScene/RPBox_802f9f50
- source: unit sweep 2026-11-01

symptom: 98.5% pure register residue: e/child folded into operator-new result temps that outrank the hoisted -1/0/vtable constants
cause: back-end CopyPropagation runs once in program order and refuses a copy whose use is itself a move; named locals are numbered in reverse declaration order
fix: void* ev, cv declared first; ev = operator new(..); e = (BoxItem*)ev; same for cv/child (R17 row 50). Dead: e = new BoxItemNew(i,self) offset loop 98.5, child = new BoxChildNew(e) 98.5, single void* in loop body 98.1, indexed loop 94.4
