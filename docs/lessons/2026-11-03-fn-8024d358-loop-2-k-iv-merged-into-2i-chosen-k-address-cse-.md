# fn_8024D358 loop 2: k IV merged into 2i, chosen[k] address CSE'd across if/else join (parked 97.1)

- status: open
- tags: RPTnsScene,iv,strength-reduction,cse,fn_8024D358
- scope: Pack/RPSports/RPTnsScene/RPTns_8024c194

symptom: fn_8024D358 97.1: target keeps k=2i+1 as its own IV (li 1, +2) plus offset IV k*4 and single hoisted base copies (mr r20,chosen; mr r19,related) used via stwx/lwzx; ours rewrites k as addi 2i+1, uses two related-base copies and CSEs &chosen[k] into one vreg across the if/else join (stwux + lwz 0(rX))
cause: mwcc_dbg: frontend (backend-00) still has k as IV r109; backend optimizer replaces it by r106(2i)+1. Frontend IV increment order = first-use order (self, k, chosen, related, 2i); target implies (self, chosen, k, related, 2i). Address CSE comes from the IRO making &chosen[k] available at the join.
fix: Wins kept: info2.mIconWidth/Height=0x80 re-set after the copy ctor (0x9c/0x9e store order, 96.4->97.1) and 's32 i = 7; s32 maxId = 0;' order (volatile r5/r6 swap). Lead (not kept, steering): 's32* cho = chosen; s32* rel = related;' before the loop for the [k] accesses (single base copies, 97.6) + 's32 k;' assigned 'k = i*2+1' inside each branch after the chosen[i*2] store (kills the join CSE, 98.3), k still merged. Dead ends: explicit for-IVs (e,k / k only), k-1 indices, inline i*2+1 everywhere, loads via chosen[i*2+1], common tail after if/else, pointer args, decl-order of first/j/k/second, inline helper for the pair selection (transparent).
