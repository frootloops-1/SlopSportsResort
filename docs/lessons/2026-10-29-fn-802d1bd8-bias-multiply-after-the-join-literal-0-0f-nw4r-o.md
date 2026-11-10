# fn_802D1BD8: bias multiply after the join, literal 0.0f, nw4r-order VEC3Scale copy

- status: works
- tags: fn_802D1BD8,RPBox_802cf93c,ternary,paired-single,inline-asm
- scope: RPBox_802cf93c

symptom: fmuls inside the if arm instead of after the join; extsb r0 vs r5; ps_muls0/psq_st order differed (95.6)
cause: inline returned speed*bias inside the if; zero was an extern (no CSE with bias's 0.0f); PodScale asm had Z load before XY store
fix: static inline: return speed * (sign*speed >= 0.0f ? owner->f3F4 : 0.0f); f32 zero = 0.0f; file-local copy of nw4r VEC3Scale (psq_l/muls/psq_st XY then Z) for out->pos = X*a -> 98.4. Remaining: a in f4 vs f1 (removing local a 97.1), r7/r8 owner vs &dd in the state==8 block (BoxLimitReach helper 128 lines, worse)
