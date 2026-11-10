# fn_801E7EB4 (RPSports_801E7EB4): colouring and post-RA scheduling interact (hw must take f0 so fdivs stays before lfd)

- status: fails
- tags: regalloc,fpr,schedule
- scope: RPSports_801E7EB4 fn_801E7EB4
- source: FPR batch 2 2026-10-28

symptom: 99.29
cause: inlining hh gives the target colours for quotient and hh but hw loses f0 and fdivs moves after lfd (best 4 diff lines, 95.0)
fix: none: inline hh/hw into ctor args, 6 decl permutations, member-wise pos.x/pos.y, named quotient, per-axis inline psRatio (93.8). park
