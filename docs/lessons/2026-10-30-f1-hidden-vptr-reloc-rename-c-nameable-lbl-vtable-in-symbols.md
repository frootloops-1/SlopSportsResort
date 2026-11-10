# F1 hidden vptr reloc: rename C-nameable lbl_ vtable in symbols.txt, hand vptr store for template vtable

- status: works
- tags: F1,hidden,vptr,symbols,RPGol
- scope: RPGol_802b4f2c

symptom: fn_802B54A0 99.68: lis/addi reloc names __vt__GolSndActor / __vt__22TRPSndAudioHandles<10> vs lbl_803C7D28/90
cause: compiler emits real vtable refs; target symbols are nameless lbl_
fix: rename lbl_803C7D28 to __vt__11GolSndActor in symbols.txt (+externs in users); for the <10> template vtable add R17 hand vptr store in handles ctor AND build the SoundHandle array by hand (u8[N][4] + __construct_array) so the store precedes it; 99.68 -> 100. Hand store alone after member-array ctor does not drop the compiler store.
