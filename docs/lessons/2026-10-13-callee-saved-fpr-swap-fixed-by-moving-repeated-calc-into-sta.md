# Callee-saved FPR swap fixed by moving repeated calc into static inline

- status: works
- tags: regalloc,fpr,inline
- scope: RPGol_802c441c
- source: claude/rpgolscene-unsplit

symptom: two long-lived floats in swapped callee-saved FPRs
cause: vreg creation order
fix: move the repeated calculation (angle = fn_802A39BC + 57.29578f*abs(...)) into a static inline helper; decl order did not help
