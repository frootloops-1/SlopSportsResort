# fn_802029C4 closed: u32 v = (u32)__cntlzw(x - k) >> 5 local for all three visibility bits

- status: works
- tags: cntlzw,bit-insert,RPSports_80201240
- scope: Pack/RPSports/RPSportsCommon/RPSports_80201240
- source: claude/sp80201-1104

symptom: x == k with k != 0 compiled to srwi + rlwimi(byte) instead of rlwinm + rlwimi(cntlzw,27,31,31)
cause: bool compare form lets the compiler pick the other insert operand
fix: v = (u32)__cntlzw(self->f24C - k) >> 5; *f = (*f & 0xFE) | v; (direct inline __cntlzw in the expression did not match; bitfield struct was worse)
