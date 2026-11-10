# fn_803380DC (RPBow_80335DB0): Tns R17 hand vptr store closes the last reloc-name lines (99.84 -> 100, unit 9/9)

- status: works
- tags: RPBow_80335DB0,fn_803380DC,sound-actor,lbl_803C3FF8,R17,vptr
- scope: RPBow_80335DB0
- source: claude/ren-bow-1028 sonnet

symptom: after class model + lbl_803CA588 rename, 4 lines: lis/addi on __vt__21TRPSndAudioHandles<8> vs retail lbl_803C3FF8
cause: retail handles vtable is the shared lbl_803C3FF8; mangled name not writable in C; renaming it would break 16 other source files (one Matching)
fix: In the local TRPSndAudioHandles<8> specialisation ctor add *(void**)this = lbl_803C3FF8; before the hand __construct_array (class stays polymorphic; compiler vptr store dead and dropped). MATCH-PENDING (R17), ledger row 29. No new .data atoms. First attempt worked
