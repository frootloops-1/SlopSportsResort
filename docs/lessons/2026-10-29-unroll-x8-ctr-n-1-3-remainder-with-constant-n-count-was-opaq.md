# Unroll x8 + ctr (n-1)>>3 + remainder with constant n: count was opaque at unroll time

- status: works
- tags: unroll,loop,mwcc,iro,802c8360,rpbox
- scope: mwcc
- source: claude/y-box8360-1029

symptom: orig loop over constant n=80: li r0,9 ctr, x8 body keeping i (addi r5,r5,8), remainder subfic r0,r5,0x50/cmpwi r5,0x50/bge; ours picks a divisor factor (16 signed, 10 unsigned) and no remainder
cause: MWCC IRO unrolls a loop with a CONSTANT trip count by an even divisor; the variable-count unroller (x8, prechecks n>0, n>8, 0x7FFFFFFE) is used when the bound is not yet constant; later IRO folding turns its checks into li/subfic/cmpwi. A copy chain or u32->int conversion still folds before unrolling; arithmetic on a propagated variable (int a=40; b=a*2 / a+40) does not. cmpw (signed) remainder needs int i AND int n; int i < u32 n gives srwi./andi. form instead. Also: a 6-trip loop that went the same variable path ends up fully unrolled with an frsp+stfs chain (the remainder loop re-unrolled), which looks like the unsigned constant path
fix: pass the count as arithmetic on a local (u32 nAll=86; nS=nAll-80; nL=nAll-nS) into an int n ctor param; MATCH-PENDING marker since the real expression is unknown
