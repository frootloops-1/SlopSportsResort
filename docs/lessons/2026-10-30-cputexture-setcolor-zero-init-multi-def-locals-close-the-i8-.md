# CpuTexture setColor: zero-init + |= multi-def locals close the I8 colouring wall

- status: works
- tags: cputexture,setcolor,egg,regalloc,iro,forwarding,marker
- scope: egg/gfxe/eggCpuTexture

symptom: Single-use locals (red byte, offset) are copy-propagated by IRO: red loads at the use (highest vreg, coloured first -> r0) and a single-def offset reassociates buf+(blk+pix) into (buf+blk)+pix
cause: Colouring is in descending vreg order; target needs red evaluated before the pixel temps and an unreassociated blk+pix sum
fix: u8 r = 0; r |= color.r; int offset = 0; offset |= blk*32 + pix; (MATCH-PENDING R17, ledger row 33). Multi-def blocks forwarding; 0| folds later. offset trick alone 16 lines; += instead of |= reassociates and commutes pix add (2 lines). Single-expression store gives red-first but reassociates (40 lines).
