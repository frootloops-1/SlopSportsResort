# ScreenEffectBase sWorkBuffer sdata size 8 -> 4

- status: works
- tags: symbols,sdata,egg,ScreenEffectBase
- source: claude/sfx-1027

symptom: unit_cmp sWorkBuffer 66.7, SIZE-MISMATCH 8!=4, .sdata 66.67
cause: symbols.txt gave the 4-byte enum static size 0x8 (included the sdata alignment pad)
fix: set size:0x4, re-split; .sdata 100, DOL 0 bytes
