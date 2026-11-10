# fn_80281A88 (RPBsb_802817a0) 97.3: store-to-load forwarding frsp into unrolled copyMtx load

- status: fails
- tags: rpbsb,fpr,frsp,forwarding,copymtx,unroll
- source: claude/bsb-1a88-1103f

symptom: Ours adds frsp f0,f11 for the first copyMtx load of m2[0][0]; retail reloads lfs f5,0xa8(r1), colours f0,f9,f6,f5,f8,f7 for cols 0/1
cause: frsp absent from backend-00, introduced by the pre-RA optimizer: store-to-load forwarding after the copyMtx outer loop is unrolled at pcode level
fix: Not closed. Dead: m2 build before objs[1]->copyMtx 77.2; cols 2/3 via setBase identical; cols 0/1 nested loop removes frsp but 2 rotating vregs not 6 (96.4); setMtx straight-line forwards everything 89.2; opt_propagation/common_subs/lifetimes/dead_code off no effect. Untested: a basic-block boundary between the m2 stores and the copy loop, or a store-address form not yet folded to r1+offset when forwarding runs
