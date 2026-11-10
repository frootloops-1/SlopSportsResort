# Switch tree {4: empty, 5: body} root=smaller case + range leaf not reproducible

- status: fails
- tags: switch,decision-tree
- scope: RPTns_802318a4
- source: claude/rptns-2

symptom: orig: cmpwi 4; beq exit; bge R; b exit; R: cmpwi 6; bge exit; body. Every {4,5}/{4,5,+one empty 0..10} switch and if-chain gives cmpwi 5-first or blt exit; stuck at 99.1
cause: unknown; pairs normally root at the LARGER case (7 of {6,7}, 8 of {7,8})
fix: none found; brute-forced empty-case sets and if/else forms
