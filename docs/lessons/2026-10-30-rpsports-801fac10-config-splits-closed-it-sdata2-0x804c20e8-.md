# RPSports_801fac10: config splits closed it (sdata2 0x804C20E8 split + lbl_803C2FE8 split into four 0xC PTMF objects)

- status: works
- tags: data,split,ptmf,sdata2,symbols,RPSports_801fac10
- scope: Pack/RPSports/RPSportsCommon/RPSports_801fac10

symptom: fn_801FB91C 99.2 (objdiff synthesized reloc lbl_803C2FE8+0xC vs separate static), fn_801FAF28 not exact (1.0f in neighbour's .sdata2)
cause: dtk merged four compiler PTMF constants into one 0x30 lbl_; the new TU's .sdata2 (0x804C20E8-0x804C20F0) was still assigned to the old unit
fix: symbols.txt lbl_803C2FE8 0xC + lbl_803C2FF4/3000/300C 0xC, file-statics renamed to them; splits .sdata2 boundary 0x804C20E8 -> unit 9/9 exact, .text/.data 100, link + DOL 0 when flipped. .sdata2 shows 66.67 only from dtk's trailing gap_12_804C20EC pad (same as Matching RPSports_801ed7d8).
