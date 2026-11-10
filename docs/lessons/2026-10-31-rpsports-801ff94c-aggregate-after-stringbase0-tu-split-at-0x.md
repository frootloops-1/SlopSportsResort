# RPSports_801ff94c: aggregate after @stringBase0 = TU split at 0x801FFCF8, both halves flip

- status: works
- tags: tu-split,rodata,stringBase0,RPSports_801ff94c
- source: claude/sp-ff94c-20261031

symptom: 16/16 fns exact, sections 100, but flipped DOL differed by 124 B: local aggregate @1842 (fn_801FFD00) had to sit after FFA20's string pool; every in-TU lever failed
cause: string pool closes a TU's .rodata; @1842 and all .data/.sdata2 belong to a second TU starting at fn_801FFCF8 (RoParamObj setter, same class as FFE88..FFE98)
fix: splits: 801ff94c = .text FF94C-FFCF8 + .rodata 895B0-89610; new RPSports_801ffcf8 = .text FFCF8-FFEC0, .rodata 89610-89638, .data 3188-3198, .sdata2 2160-2178; source split, keep reverse order; DOL 0, both Matching
