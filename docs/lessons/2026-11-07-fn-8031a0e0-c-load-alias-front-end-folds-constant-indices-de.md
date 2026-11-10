# fn_8031A0E0 c-load alias: front-end folds constant indices; dead ends for whole-V c

- status: fails
- tags: A0E0,alias
- scope: fn_8031A0E0
- source: round 8

symptom: Trying to give prm->pC4 load an imprecise alias with plain lfs 0xc4(r31)
cause: IRO folds (&pC0)[1], int ci=1 (same or earlier block), member pointers, inline index helpers, p++ and 1-trip loops before the backend, so the alias stays precise (all identical, 112). type*0x62 (lfsx, 122) and asm li in another block (119) do get whole-V.
fix: None natural yet; asm li in a prior block is the only working lever (not committed).
