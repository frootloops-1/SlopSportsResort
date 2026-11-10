# fn_802D7B24: missing instruction is a dead d.x store (stfs 0x98 twice) that retail keeps

- status: open
- tags: fn_802D7B24,RPBox_802cf93c,size-mismatch,dead-store
- scope: RPBox_802cf93c
- source: claude/box802cf-r2-1029 opus

symptom: 1800 vs 1796 bytes: target stfs m108[0][1] to d.x, then stfs d.x*0.8 to the same slot; ours stores once (rest is FPR numbering)
cause: the original's first d.x store is not dead-store-eliminated; the access path or type differs from a plain BoxV3Pod local
fix: failed: BoxVec3 ctor d(x,1,0) then d.x*=0.8 (98.6), aggregate init (96.5), stores through BoxV3Pod* pd (same), scale after all three stores (149 lines)
