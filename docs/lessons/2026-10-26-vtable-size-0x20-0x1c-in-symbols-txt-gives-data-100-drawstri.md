# Vtable size 0x20 -> 0x1C in symbols.txt gives .data 100% (DrawStripeStrategy vt)

- status: works
- tags: vtable,symbols,gap,padding,nw4r
- scope: ef_drawstripestrategy

symptom: .data 98.73%, vt size-mismatch 32!=28
cause: Symbol included 4 bytes of alignment padding
fix: size:0x1C, dtk dol split --no-update adds the gap_; DOL stays 0 diff
