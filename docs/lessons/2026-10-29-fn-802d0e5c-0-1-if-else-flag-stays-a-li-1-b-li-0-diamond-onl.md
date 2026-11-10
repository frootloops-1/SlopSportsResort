# fn_802D0E5C: 0/1 if/else flag stays a li 1/b/li 0 diamond only when an arm holds one more (dead) statement

- status: works
- tags: fn_802D0E5C,RPBox_802cf93c,mfcr,diamond,compare-value,dead-store
- scope: RPBox_802cf93c
- source: claude/box802cf-r5-1029 opus

symptom: target flag = (x >= 0) as cror;bne;li 1;b;li 0; every plain spelling (if/else, ?:, bool, u8, switch, goto, !(x<0), init+if) folds to mfcr/rlwinm or hoists li 0
cause: an IR pass folds an if/else whose arms are exactly flag=1 / flag=0 into a compare-value; any extra statement in an arm (dead float store, an else-if whose arms later merge) blocks it and the later DCE leaves the diamond
fix: else { flag = 0; dead = 1.0f; } (f32 dead, MATCH-PENDING) -> 98.8, size now equal; else-if (x < 0) flag = 0; else flag = 0 also gives the diamond. sign = -sign in the arm instead: 93.5. Rest is colouring
