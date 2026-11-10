# Pane visible bit SetBit form at +0xB7

- status: works
- tags: nw4r,lyt,pane
- scope: RPGol_802bf4f8
- source: opus-worker

symptom: need rlwinm 24,30 + ori for visibility
cause: nw4r SetBit pattern
fix: flag &= ~1; flag |= b ? 1 : 0 on u8 at +0xB7 (glb mtx at +0x84)
