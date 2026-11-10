# fn_802D9850 (RPBox_802cf93c): invented case labels cause join-moved; case 9: return closes 92.2->96.3

- status: works
- tags: fn_802D9850,RPBox_802cf93c,switch,join-moved,branch-shape
- scope: RPBox_802cf93c
- source: claude/box3-1028 sonnet

symptom: beq/bge/cmpwi 0xb tail and reordered compares in a 108B switch (join-moved, fewer-cmp)
cause: invented case 0/case 11 labels added compare nodes; a break body for case 9 is threaded away so the second trailing b is lost
fix: switch(lbl_804BDC0C){case 9: return; case 1: body; break; default: break;} (default: return with case 9: break also 96.3)
