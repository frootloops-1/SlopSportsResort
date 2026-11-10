# Local aggregate init u8 x[1]={0xE5} makes a lbz-from-sdata2 template (fixes pf_entry); a static u8 global folds or lands in sdata

- status: works
- tags: sdata2,aggregate,template,vf
- scope: revolution/VF

symptom: pf_entry 100% fns but sdata 1B extra and sdata2 8B missing; DOL 33k bytes
cause: FAT_DELETED was a static u8 global; original used a local array initializer which MWCC loads from a sdata2 template
fix: u8 dir_fb_free[1] = {0xE5}; (drop the global); const/volatile global variants fold to li
