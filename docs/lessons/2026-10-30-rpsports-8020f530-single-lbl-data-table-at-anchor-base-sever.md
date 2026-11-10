# RPSports_8020f530: single lbl_ data table at anchor base = several same-TU statics; split in symbols.txt

- status: works
- tags: hidden,data.0,anchor,symbols,rpsports
- source: worktree f1-sp8020f530

symptom: fn_8020F96C 99.6 and fn_8020FB5C: reloc lbl_803C35F8 vs ...data.0 anchor; extern table struct regressed to 90%
cause: orig lbl_803C35F8 (0xD0) was 3 file statics + 4 function-local-style name arrays (sizes inferred from the n[k] index groups); >=3 same-TU objects makes the compiler use the anchor base
fix: symbols.txt: split lbl into local sBtnNames/sGraphNames/sPaneNames/sAnimNamesA-D; define each as static array in source (pointers as lbl_8038AB50+off); both fns 100, .data 7->51%
