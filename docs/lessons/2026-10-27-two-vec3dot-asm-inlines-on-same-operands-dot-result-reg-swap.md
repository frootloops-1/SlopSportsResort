# Two VEC3Dot asm inlines on same operands: dot result reg swaps with fsubs projection

- status: works
- tags: mwcc,fpr,VEC3Dot,inline,register
- scope: Pack/RPUtility/RPUtlRigid

symptom: second VEC3Dot ps_sum0 dest took work1 reg instead of work0; projection fsubs reg swapped (RPUtlRigid fn_801B9EC0/fn_801BA284)
cause: projection inline written as 'return VEC3Dot(n,v) - d;'
fix: inline body 'float dot = VEC3Dot(n, v); dot -= d; return dot;' closed fn_801B9EC0; also check dot operand order from ps_mul/ps_madd operands
