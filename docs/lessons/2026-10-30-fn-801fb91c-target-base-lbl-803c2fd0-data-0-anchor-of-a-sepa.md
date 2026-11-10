# fn_801FB91C: target base lbl_803C2FD0 = ...data.0 anchor of a separate TU (splits decision)

- status: open
- tags: data,split,ptmf,anchor,RPSports_801f9150
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f9150

symptom: instructions exact, base reloc ours ...data.0+0x88/0xe8 vs target lbl_803C2FD0+0x24/0x30/0x3C
cause: MWCC addresses local/anonymous .data through the section-start anchor ...data.0; the target anchor is 0x803C2FD0, so fn_801FAC10..fn_801FB91C (.text 0x801FAC10-0x801FBA3C, .data 0x803C2FD0-0x803C3018, no rodata/sdata2/sbss of its own) is its own TU. Also: real &Cls::fn PTMF emitted an undefined fn_801FB874__6SpQ874Fv (link break).
fix: orchestrator: split RPSports_801f9150 at 0x801FAC10/.data 0x803C2FD0 into a new unit. In-unit: file-static {0,-1,(void*)fn} records give identical code and link (no mangled member).
