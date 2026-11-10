# RPSports_801f125c: second string pool + vtable in other TU -> split unit; flip needs descending source order

- status: works
- tags: rodata,stringBase0,split,vtable,order
- scope: RPSports_801f125c

symptom: Flip failed with undefined lbl_ data; defined strings deduped into one pool (0x56) but target has Cursol twice (0x58 pool + separate 8-aligned Cursol)
cause: Missed TU boundary at 0x801F18E8 (second @stringBase0 at 0x80387E38, .data vtable belongs to second TU); also source order was not descending so text emission order was wrong
fix: Split into RPSports_801f125c + RPSports_801f18e8, define vtable as extern C void* lbl_803C29A0[4], floats/strings as literals, reorder fns descending with reorder_fn.py; DOL 0
