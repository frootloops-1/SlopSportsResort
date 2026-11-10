# Clear bit 0 of u8: &= 0xFE not &= ~1

- status: works
- tags: mwcc,bits
- scope: RPGol_802bca94
- source: sonnet-worker

symptom: need rlwinm 24,30
cause: ~1 emits clrrwi
fix: flags &= 0xFE; set: (flags & 0xFE) | 1
