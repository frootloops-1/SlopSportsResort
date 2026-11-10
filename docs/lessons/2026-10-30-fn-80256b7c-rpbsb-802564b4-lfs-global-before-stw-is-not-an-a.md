# fn_80256B7C (RPBsb_802564b4): lfs global before stw is not an alias/restrict/volatile issue

- status: fails
- tags: RPBsb,schedule,alias,park
- scope: fn_80256B7C
- source: worker nm64b4 2026-10-31

symptom: target lfs lbl_804BF78C before stw hit->ignoreId and fadds before li ret,0; ours lfs after the vtable lwz
cause: mwcc_dbg: pre-RA IR keeps lfs after the stw (memory dep); target IR order unknown
fix: Failed: static or volatile global, *(const f32*)& read, __restrict removed (no effect at all), sum local before/after store (copy-propagated), inline wrapper containing the store (95.4), wrapper + flag loaded first (95.7: lfs position right, lbz/li ret wrong), ret=0 at top (95.6) or after the call (96.1)
