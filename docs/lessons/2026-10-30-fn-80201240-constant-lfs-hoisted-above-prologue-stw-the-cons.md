# fn_80201240: constant lfs hoisted above prologue stw -> the 'constants' are .sdata globals, declare non-const extern f32

- status: works
- tags: scheduling,post-ra,sdata,extern-const,prologue,RPSports_80201240
- scope: Pack/RPSports/RPSportsCommon/RPSports_80201240

symptom: post-RA scheduler hoists two sda21 lfs above 'stw r0,0x224(r1)'; mwcc_dbg after-peephole order already equals target, only the final schedule differs
cause: lbl_804BDD30/34 are in .sdata (symbols.txt), i.e. non-const globals; 'extern const f32' lets the scheduler move the loads past stores
fix: extern f32 lbl_804BDD30/34 (non-const, no marker): 94.6 -> 100. General: when a global lfs/lwz is hoisted above a store, check symbols.txt section (.sdata = non-const). Other RPSports units still declare them const.
