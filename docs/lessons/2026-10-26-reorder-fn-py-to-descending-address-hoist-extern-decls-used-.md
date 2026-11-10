# reorder_fn.py to descending address: hoist extern decls used by moved functions

- status: works
- tags: order,reorder_fn,RPSports
- source: ord-c-1026

symptom: After reorder_fn.py reversing function blocks, compile fails with undefined identifier for an extern declared between the old function positions
cause: externs/structs declared mid-list are now below the first user
fix: Move the extern declarations above the function list (RPSports_801f6a40: lbl_804C20A0, fn_801EAA34, fn_801D8654, fn_801FABB0); codegen unaffected, then flip: dol_diff 0, shasum OK, sym_addr_check 4 known
