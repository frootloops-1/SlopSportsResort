# RPSndAudioMgr.h/RPGraphics.h/RPKernel.h pull g3d_gpu.h cm2hw+0xD7 pad into .sdata2

- status: open
- tags: sdata2,include,cm2hw,g3d
- scope: RPGolMain

symptom: built .sdata2 has leading cm2hw[4]+D7 pad, floats shifted 8 bytes vs orig; reloc-only mismatches (99.3%)
cause: g3d_gpu.h static const u8 cm2hw[] emitted by any TU including these
fix: see RPSports_801CE7F8.cpp: drop shared includes and declare local views of only what is called
