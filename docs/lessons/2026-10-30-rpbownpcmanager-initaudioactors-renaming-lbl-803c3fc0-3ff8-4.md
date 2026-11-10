# RPBowNpcManager InitAudioActors: renaming lbl_803C3FC0/3FF8/4080/4098 gives 100% code but breaks DOL link

- status: open
- tags: f1,symbols,hidden,rpbow,weak,template,link
- scope: RPBowNpcManager; config/RSPE01_01/symbols.txt
- source: claude/f1-bownpc-1031 worker report 2026-10-31

symptom: InitAudioActors 99.54%, 9 words wrong; inlined TRPSndAudio3DActor<4> ctor emits its own weak .data symbols while the target references the same bytes as lbl_ names with no split here
cause: Renaming the four lbl_ symbols to our emitted weak template vtable/@STRING@ names reaches 100% code, but 17 other RPBow/RPGol/RPBsb/RPBox/RPTns sources extern the lbl_ names (some in hand vptr stores), so mwldeppc fails with undefined lbl_803C4098 etc; template-mangled names cannot be written as C++ externs
fix: Not applied (reverted). Needs a cross-unit change: give the four .data symbols their own split or shared unit and rewrite the 17 externs to real template vtables. Run grep -rl lbl_<addr> src before any such rename.
