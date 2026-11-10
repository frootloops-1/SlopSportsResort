# LoadScnLightInner: no zero-code loop exit found; backend never folds the extra compare

- status: fails
- tags: regalloc,LightManager,induction,IRO,loop,egg
- scope: egg/gfxe/eggLightManager

symptom: k1-style top break gives retail regs + ctr but leaves a compare
cause: IRO folds constant/range-provable conditions (and then rotates to the pointer form); any condition it keeps survives into the backend, even cmplw rX,rX
fix: failed: this==NULL / ptr()!=copy break (2 lines left), lightNum<0, (u32)i>0xFFFFFFFF, i>INT_MAX, (u8)x>0xFF, (u16)i>0xFFFF (folded), &member==NULL, this==&m_scn (13 lines), &lightSet==NULL (132)
