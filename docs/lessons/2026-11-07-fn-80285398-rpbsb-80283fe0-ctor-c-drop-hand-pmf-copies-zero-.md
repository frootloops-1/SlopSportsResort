# fn_80285398 (RPBsb_80283fe0) ctor C: drop hand PMF copies, zero cur/prev before cam/scr

- status: open
- tags: RPBsb_80283fe0,ptmf,ctor,scheduling,reloc
- scope: RPBsb_80283fe0

symptom: C ctor 93.4 with asm's hand lbl_803C7158 PMF copies present (refs ...data.0+0x48)
cause: the C emits its own @16769.. PMF constants; the hand copies (force_active) shift them
fix: remove hand copies when using C, order rects before cam/scr: 14 diffs left (retail issues 6 PMF addi before sth d0/d2, cam/scr after mr r3; chained a=b=0 and cam/scr after init worse) and reloc names ...data.0 vs lbl_803C7158
