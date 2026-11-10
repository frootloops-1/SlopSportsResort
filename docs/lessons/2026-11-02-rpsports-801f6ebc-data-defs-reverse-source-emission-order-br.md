# RPSports_801f6ebc: data defs + reverse-source emission order bring DOL to 77 bytes

- status: works
- tags: RPSports,emission-order,sdata2,vtable,reorder_fn
- scope: RPSports_801f6ebc

symptom: unit 59/61 but .data/.sbss/.sdata2 at 0/0/50% and flip_gate 5109 bytes
cause: vtables/f32 consts/sbss string undefined; TU emits text in REVERSE source order and source had a block ascending
fix: define void* lbl[6]={0,0,fn,fn,fn,0} x2, extern const f32 1000/10/0.1/0.0 (0.0 fills the gap word), wchar_t lbl_804BF738[4] at file end; reorder_fn.py moves for the non-LIS functions (LIS of descending address), add forward proto for fn moved below caller; flip_gate then only fn_801F7150/fn_801F7B80 (77 bytes)
