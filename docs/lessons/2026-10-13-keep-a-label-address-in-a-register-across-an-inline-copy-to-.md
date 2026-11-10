# Keep a label address in a register across an inline: copy to a local pointer

- status: works
- tags: address,lis,addi,inline
- scope: RPGol_802c16a4
- source: claude/rpgolscene-unsplit

symptom: orig lis/addi once then lbz 0(rX); ours folds sym@l(rX)
cause: array passed directly
fix: const char* name = lbl; then call the inline with name
