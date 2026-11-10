# fn_80222E98 pass 4: copying the pointer into a variable assigned in both arms of an if/else keeps its addi, and the copies disappear

- status: open
- tags: addi,fold,add-propagation,join,copy,RPTns_80222a70,fn_80222E98
- scope: Pack/RPSports/RPTnsScene/RPTns_80222a70
- source: claude/tns-2e98-1103 pass 2

symptom: need a use that blocks the addi fold of rad/rsq and leaves no code
cause: Copies into a variable with 2 defs (both arms of an if/else, used after the if) survive IRO. The backend still sees the mr, which blocks add-prop, and later removes it. Rewriting FSqrt as if(sq<=0){dist=0;r2=rad;}else{dist=sq*FrSqrt(sq);r2=rad;} with pen using *r2 keeps rad's addi r31 (96.3). rsq has no if/else before its compare, so it still folds, and post-RA value numbering then rewrites rad's early loads as 0x14(r5). Adding if(a!=b) q2=rsq; else q2=&a->mgr->f18; with the compare done through *q2 gives the target body plus ONE cmplw r3,r4 and an f0/f1 swap (7 lines). Backend removes the empty arms' branch but never the compare.
fix: open: need an if/else before the rsq compare whose condition costs no instruction. Failed: identical-arm if/else (IRO merges), conditions that IRO cannot fold but the backend keeps (cmplw/fcmpo/cntlzw), single-iteration for/do loops, null-test through the join (extra li/cmpwi, 12 lines), base re-load or variable reuse (IRO renames), union overwrite (backend keeps dead stw), flags -ipa file/-inline auto/-O4,s/-opt nopeephole, unit cflags vs forecast not applicable (Pack)
