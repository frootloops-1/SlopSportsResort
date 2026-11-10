# fn_80268A30 / RPBsb_802656a4: .sdata2 fixed with literals; li r3,0x68 hoist is a block-split wall

- status: fails
- tags: RPBsb_802656a4,fn_80268A30,sdata2,scheduler
- scope: Pack/RPSports/RPBsbScene/RPBsb_802656a4

symptom: sdata2 0% (extern const f32 pool floats emit no section); fn_80268A30 98.4: li r3,0x68 lands ~8 insns later
cause: backend splits the unrolled st[6] clear loop block after ~100 insns; target split is before st[4].obj, ours before st[4].b
fix: sdata2: float literals + local @N renames in symbols.txt (works, 100%). Code: clear() inline, static helper, per-iter pointer, hand unroll (97.6), pointer loop (71.0), vt28 after loop all fail; untested: real class model with array-member ctor
