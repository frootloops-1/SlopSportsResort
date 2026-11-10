# RPBox_802e2a84: non-const sdata2 colour via __declspec(section)

- status: works
- tags: sdata2,section,rpbox,fn_802E5920
- source: tb-e2a84

symptom: lbl_804C5018 4-byte colour defined non-const lands in .sdata (sdata2 97.56); const fixes section but folds/hoists loads (fn_802E5920 96.4 -> 89.3)
cause: target data is in .sdata2 but accessed as non-const
fix: extern "C" __declspec(section ".sdata2") _GXColor lbl = {...}; defined before first use (end of file breaks pool order, 95.2). Code residue (sda address CSE li r5,sym) unsolved: unroll, loop, struct copy, local copy, const all no gain
