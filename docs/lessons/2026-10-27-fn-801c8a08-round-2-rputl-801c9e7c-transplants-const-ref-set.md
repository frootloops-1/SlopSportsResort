# fn_801C8A08 round 2: RPUtl_801C9E7C transplants (const-ref set, Size-like copy ctor, const u8 origin) do not move the set(pane) wall

- status: fails
- tags: fn_801C8A08,RPUtlLytFrameCursor,RPUtl_801C9E7C,schedule,CSE
- scope: function

symptom: same 8x set(pane) size-lfs/stack-lfs late, r6 vs r10 origin, pane+0x88 r27 CSE wall as fn_801CA3DC
cause: unknown; shared by both cursor units
fix: failed (identical output): u8 horizontal/vertical after mtx copy, const u8 origin, set(const Descriptor&), Pair copy ctor with body assignments, combined
