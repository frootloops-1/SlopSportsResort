# fn_8031A0E0 wall 2/3 dead ends (round 10)

- status: fails
- tags: A0E0,RPBow,rate,tEF4,cse,regalloc
- scope: fn_8031A0E0
- source: round 10

symptom: rate f6/f7 pressure; (j+1)*16 vs base+k*16 GPR swap; block-2 schedule with VEC3* h
cause: Rate lerp operand forms all compile identically (IRO canonicalises); statement perms flat. IRO CSE temps get vregs in reverse creation order and are created at the 2nd use in linear order, so base+k*16 (P.y) outranks (j+1)*16 (P.z). P.x stack reload loses to the Q-ctor load on the pending==1 tie-break
fix: Dead: 81 lerp spellings, 24 lerp orders, 360 tEF4 statement orders with h (best 86 > 78 without h), named row-value locals (drop the h addi), P.x += spellings, flag P.x = -P.x. Open: create (j+1)*16 temp first without moving P.z
