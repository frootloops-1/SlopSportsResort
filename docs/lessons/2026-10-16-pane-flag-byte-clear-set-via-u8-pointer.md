# pane flag byte clear/set via u8 pointer

- status: works
- tags: bitfield,rlwimi,rpbsb
- source: RPBsb_8028bb24 2026-10-16

symptom: bitfield clear/set emits rlwimi with extra li/reload
cause: bitfield access lowering
fix: u8* p; p[0xB7] &= ~1; p[0xB7] |= 1; on one loaded pointer gives rlwinm+ori
