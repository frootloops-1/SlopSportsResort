# fn_802D930C (RPBox_802cf93c) second assignment of sel gets f21 not f31 (web split)

- status: fails
- tags: regalloc,fpr,rpbox,fn_802D930C
- scope: fn_802D930C
- source: claude/box1-1028

symptom: retail reuses f31 for sel after reassign (sel=a*(4*add+s0)); ours f21 (4 diff lines)
cause: sel1 and sel2 are separate webs in ours; retail coloured them to the same f31
fix: failed: separate var sx for second def, sel declared inside case block, sel declared after add, if/else instead of ternary (regress 99.3)
