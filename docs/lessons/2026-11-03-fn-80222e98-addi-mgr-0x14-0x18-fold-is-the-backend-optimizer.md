# fn_80222E98 addi mgr+0x14/+0x18: fold is the BACKEND optimizer, not IRO

- status: fails
- tags: addi,fold,add-propagation,RPTns_80222a70,fn_80222E98
- scope: Pack/RPSports/RPTnsScene/RPTns_80222a70

symptom: target keeps addi r31,mgr,0x14 / addi r5,r5,0x18 + lfs 0(rX); ours folds to lfs 0x14(mgr) (97.6)
cause: mwcc_dbg: backend-00 initial code HAS the addi for refs/pointer locals; backend-01 (after optimizer) folds them. So source must defeat backend add-propagation; IRO merges p=mgr; p+=5 into mgr+20 before that
fix: none: refs (97.6), named mgr local (97.6), const f32* locals (94.4; 16 lines, FPRs then match, only addi+lwz schedule differ), p=mgr;p+=5 (94.4), register keyword (94.4), base-class this-adjust getters (97.6). Next idea needs a case where the backend refuses add-propagation (address also used as call arg / multi-def base)
