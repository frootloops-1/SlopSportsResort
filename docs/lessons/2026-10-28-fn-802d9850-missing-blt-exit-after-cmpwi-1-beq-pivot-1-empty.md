# fn_802D9850: missing blt exit after cmpwi 1; beq (pivot-1 empty left subtree) not reproduced by any case set

- status: fails
- tags: fn_802D9850,RPBox_802cf93c,switch,jumptree
- scope: RPBox_802cf93c
- source: claude/box3-1028 sonnet

symptom: target cmp 9;beq;bge;cmp 1;beq;blt;b;b vs ours without blt exit (96.3)
cause: unknown; CW emits two-case {1,9} flat; {0,1,9} picks pivot 1 first; {1,9,11} adds cmpwi 0xb
fix: failed: empty break cases -2..15 singly/pairs (best {0,10} 96.1), case 0/11 return or break, case 1 first, 9 falling into 1, case 0: default: stacking. Parked pending a new hypothesis (e.g. real if/else on a range or enum type)
