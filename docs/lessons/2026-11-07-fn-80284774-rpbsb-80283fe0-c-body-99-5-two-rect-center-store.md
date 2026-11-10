# fn_80284774 (RPBsb_80283fe0) C body 99.5: two-rect center store wall

- status: fails
- tags: RPBsb_80283fe0,regalloc,fctiwz,store-order
- scope: RPBsb_80283fe0

symptom: first rect block: extrwi h/2,w/2 take r4/r0 (retail r0/r4) and cur.y stored before cur.x
cause: x-first store order (as matched fn_802843AC) fixes regs but loads sizeX before sizeY; second block reload interacts
fix: none: decl x store perms (576), s16/u16/u32 local types, half temps, center inline helper (with/without dy param), scoped blocks; best 6 diffs. park, keep asm
