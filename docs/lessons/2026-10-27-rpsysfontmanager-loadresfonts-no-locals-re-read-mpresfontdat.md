# RPSysFontManager LoadResFonts: no locals, re-read mpResFontData[i] / mpResFonts[i]->

- status: works
- tags: regalloc,locals,RPSysFontManager,flip
- scope: Pack/RPSystem/RPSysFontManager
- source: claude/fontmgr-1027 2026-10-27

symptom: LoadResFonts 99.1%: r29/r30 swap (sIsNeedResFont base vs this+i*4 entry); 25+ variants, permuter, other MWCC versions no gain.
cause: The pResFontData local and font reference changed spill-cost ordering of the hoisted bases vs the entry pointer.
fix: mpResFontData[i] = GetFileFromArchive(...); then use mpResFontData[i] and mpResFonts[i]-> directly, no locals: 100%, DOL 0. Keeping data local with mpResFonts[i]-> is 39 lines; continue + ResFont* local 34. MWCC version sweep (GC 3.0a3-3.0a5.2, Wii 1.0-1.7, PCH-less) does not change colouring.
