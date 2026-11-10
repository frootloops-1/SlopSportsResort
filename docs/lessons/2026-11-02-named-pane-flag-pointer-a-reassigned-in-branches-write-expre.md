# Named pane-flag pointer 'a' reassigned in branches: write expressions inline so the load is a temp coloured first

- status: works
- tags: regalloc,temps,RPSports
- scope: RPSports_801fba3c
- source: fn_801FBA98

symptom: fn_801FBA98 98.9: k/n/a/i register rotation (k r3,a r4 vs target k r4,a r3)
cause: named local pointer a had a lower vreg than k; inline temps are coloured before named locals
fix: no named 'a': ((SpFlagByte*)*(void**)(self+off))->fB7 = (...)|1 spelled out in every arm (CSE keeps one load); keep u8 k and s32 n=k-1
