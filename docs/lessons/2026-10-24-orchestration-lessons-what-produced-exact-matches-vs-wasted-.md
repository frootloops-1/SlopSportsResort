# Orchestration lessons: what produced exact matches vs wasted time

- status: works
- tags: process,tooling,orchestration
- scope: project
- source: claude

symptom: ~500 near-misses, mostly the hard register tail
cause: see fix
fix: DATA-REF/pool/string symbol fixes and DOL flips gave ~80% of the new exact functions at near-zero risk: run pool_renames.py --apply, then Sonnet workers per 12 DATA-REF fns with symbols.txt edit rights inside the unit's ranges. Use the objdiff reloc-name dump (asm_diff masks symbol names) and verify/near_miss percentages, not asm_diff 'identical'. Run workers in separate worktrees (lane per worktree, merge claude/closeout-<lane> back; ninja is not safe concurrently in one tree). FPR/GPR-numbering-only 99.9% fns almost never close by hand or permuter: do not batch them. Check upstream (main) before each batch so work is not duplicated
