# fn_8029CA4C: orig lfsu f0,0x18(r3) then 4(r3),8(r3) for 3 zero-compares not reproduced (92.2%)

- status: open
- tags: rpgolconfig,lfsu,pointer-update
- scope: RPGolConfig
- source: sonnet

symptom: lfs 0x18/0x1c/0x20 instead of lfsu
cause: unknown
fix: tried GolVec3* helper, f32* v[i], v+=6, unrolled loop (59.5%)
