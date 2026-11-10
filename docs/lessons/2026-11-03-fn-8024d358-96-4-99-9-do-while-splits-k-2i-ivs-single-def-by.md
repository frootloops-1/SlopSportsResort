# fn_8024D358 96.4 -> 99.9: do-while splits k/2i IVs, single-def byte offset gives the k*4 IV, declaration groups order named vregs

- status: works
- tags: RPTnsScene,iv,strength-reduction,cse,colouring,do-while,fn_8024D358
- scope: Pack/RPSports/RPTnsScene/RPTns_8024c194

symptom: loop 2 target keeps k=2i+1 and 2i as separate IVs plus a k*4 offset IV shared by both if/else branches and the join loads (stwx/lwzx base,off), with one hoisted base copy per array
cause: for loop: frontend CSEs i*2 into k and the back end rewrites k as 2i+1; same-value-number [k] addresses get CSEd across the if/else join; frontend IV order = first-use order; named vregs number in reverse declaration order so colouring follows declaration grouping
fix: {n=0; do {...} while(++n<4);} with header 'cp = &chosen[n*2]; k = n*2+1; s32 off = k*4;' (cp first -> IV order self,chosen,k,off,related,2n), stores '*(s32*)((u8*)cho + off)' via 's32* cho = chosen; s32* rel = related;' aliases, loads '*(s32*)((u8*)chosen + off)'; db via inline getter (late temp -> r29); regsearch --generic (hoisted row/lastId/col/cp/k, u32 j) then one declaration group 's32 n; s32 col2; s32 p; first; cho; rel;' before loop 1 for the loop-1 index p and the else-loop column col2. Left 8 lines: target IV owns the preheader addi (mr base,IV), ours the alias owns it; alias assignment position (before/after n=0, in header, inline-returned, loop-local decl) and cp/cho = cp variants did not flip it.
