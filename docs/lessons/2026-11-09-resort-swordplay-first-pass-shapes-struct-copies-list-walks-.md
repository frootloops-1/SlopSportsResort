# resort: Swordplay first-pass shapes (struct copies, list walks, bool returns, u16 bitfield clear)

- status: works
- tags: resort,swf,idioms
- scope: resort
- source: swf-template-batch-2026-11-09

symptom: first-pass functions at 70-95% on copies/loops/bools
cause: all-loads-then-stores copy = by-value struct copy from const src; serial lwz/stw = field-by-field; mr in loop check = while((cur=n)!=NULL){n=cur->next;...}; li r3,0..bnelr..li r3,1 = int r=0; if(a&&b) r=1; rlwinm 0,28,26 on lhz/sth = u16 bitfield clear
fix: use these spellings; ~10 functions went to 100
