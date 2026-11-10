# ShadowTexture Draw closed: dead-init multi-def named flags local (hand-expanded disablePixModeSync) fixes the last block

- status: works
- tags: shadowtexture,draw,regalloc,debugger,flip
- scope: egg/gfxe/eggShadowTexture

symptom: Draw tail block: volatile regs wrong (22 lines, named row) or schedule off (17 lines, inline row)
cause: flag lhz/rlwinm temps (from the disablePixModeSync inline) were created after the format chain so coloured before it, stealing r4/r5; a single-def local holding the flags is forwarded back into a temp (identical scores at every position), a branchy local breaks opcodes
fix: u16 fl = 0; fl = *(u16*)this; fl = fl & ~(1 << 7); *(u16*)this = fl; placed after 'bool intensity = ...' with the inline-row capture(x, y, false, cCaptureFormat[!alpha][intensity ? 1 : 0]). The dead 'fl = 0' makes fl a real multi-def named local (low vreg, coloured last). Result: regsearch reg=0, verify 14/14, DOL 0, unit flipped. Generalises: when an inline's temps must be coloured LAST, hand-expand it into a dead-init multi-def local (marker). The working loop was dump (mwcc_dbg.sh) -> hand colouring model -> targeted probe -> regsearch score
