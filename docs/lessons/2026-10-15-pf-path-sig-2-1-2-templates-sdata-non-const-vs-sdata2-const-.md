# pf_path sig[2] = {1,2} templates: sdata (non-const) vs sdata2 (const) split unsolved

- status: open
- tags: sdata2,sdata,template,vf
- scope: revolution/VF

symptom: pf_path 25/25 fns exact but DOL +8 in sdata (sdata 49B vs 48B, '*.' vs '*.*', sig bytes 01 02 in .sdata 0x24 and .sdata2 x3)
cause: original sig arrays are s8 sig[2]={1,2}-style aggregate init (lbz/lbz template loads); our '~','1' string-literal hack changes pooling. const arrays -> sdata2, non-const -> sdata, but sharing/pooling differs: const+non-const variants gave 21/25 fns and still sdata 45B
fix: untested: separate arrays per use in MatchFileNameWithPattern (one const one non-const), '*.' literal split (L'*.' + '*'?)
