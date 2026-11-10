# MWCC commutative add operand order follows final register numbers (higher reg first)

- status: works
- tags: regalloc,operand-order,mwcc,diagnosis
- scope: egg/gfxe/eggCpuTexture
- source: claude/cpu-1026 opus

symptom: add rD,rA,rB operand order differs from target (e.g. add r0,r4,r0 vs add r6,r6,r4) and looks like a source-order/IR clue
cause: In eggCpuTexture::setColor every commutative add prints the higher-numbered register first (target and ours alike); the operand order is a post-colouring canonicalisation, not evidence of source term order
fix: Treat a swapped add operand pair as part of the register residue; do not chase it with commuted-term source variants
