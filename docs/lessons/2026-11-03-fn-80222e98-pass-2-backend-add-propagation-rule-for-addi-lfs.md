# fn_80222E98 pass 2: backend add-propagation rule for addi+lfs 0(rX) (all-or-nothing per addi)

- status: fails
- tags: addi,fold,add-propagation,mwcc_dbg,RPTns_80222a70,fn_80222E98
- scope: Pack/RPSports/RPTnsScene/RPTns_80222a70

symptom: target keeps addi r31,mgr,0x14 / addi r5,r5,0x18 with lfs 0(rX); ours folds into lfs 0x14(mgr)
cause: dumps: backend-01 (optimizer) folds an addi into all its load/store uses only if EVERY use is foldable and the dest has a single def. An mr/call-arg use (D1) or a conditional second def (if(..) rad=0) keeps the addi and all its uses unfolded; post-RA value numbering (04) can still fold a use where the base is still in a register. Matched cases of kept addi in the repo (RPTns_80220994 fn_80220A2C/D34, RPGol fn_802C0810) are all loop-pointer induction vars (multi-def)
fix: none: needs BOTH pointers blocked (unfoldable use or 2nd def) with the blocker gone by final code. Tried pass 2: 3-axis for loop over (&d.x)[k] (IRO unrolls, 90.0, still folded, frsp), whole body in static inline with const f32*/const f32& params (86.2, folded, branch merge), duplicate pointer re-assignment before use (IRO collapses, 94.4), call-arg escape (95.9, keeps rad only). Next: a construct producing a phi/2nd def on both pointers that later DCE/VN removes
