# out-struct helpers declared as void fn(Struct* out, ...)

- status: works
- tags: struct-return,frame,rpbsb
- source: RPBsb_802803b0 2026-10-16

symptom: frame grows 0x40->0x50, extra stack copy
cause: struct-returning prototype copies result to a second slot
fix: declare the helper with an out pointer (fn_802811A0 93.4->100)
