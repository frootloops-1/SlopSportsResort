# Identical if/else branches folded: use switch for double-branch layout

- status: works
- tags: branch,switch,fold
- scope: RPTns_8022c4c8
- source: sonnet worker 2026-10-14

symptom: orig beq/b double branch for if(x==0)c=50; else c=50;
cause: CW folds identical if/else
fix: switch(x){case 0: c=50; break; default: c=50; break;} (RPTns_8022c4c8)
