# RPBox_802f6be0: Matching flip needed the first .sdata2 pool entry exported as a global

- status: works
- tags: sdata2,link,extern,matching-flip
- scope: RPBox_802f6be0
- source: claude/x-box6e80-1029

symptom: Matching flip fails DOL link: undefined lbl_804C53D0 referenced from other Box units
cause: lbl_804C53D0 is a global u16 360 (lhz sda21) that was emitted as a local @N via an unreferenced static inline table helper; other TUs extern it
fix: define 'extern const u16 lbl_804C53D0 = 360;' in the owning TU instead of the local-table helper; sdata2 stays 100%, link OK, DOL 0 bytes
