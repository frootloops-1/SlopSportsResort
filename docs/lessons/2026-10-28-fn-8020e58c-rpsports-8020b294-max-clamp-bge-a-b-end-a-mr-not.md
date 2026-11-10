# fn_8020E58C (RPSports_8020b294): max-clamp 'bge A; b End; A: mr' not produced by if/ternary/inline forms

- status: fails
- tags: fn_8020E58C,RPSports_8020b294,clamp,branch-shape,ternary
- scope: RPSports_8020b294
- source: claude/sports3-1028 sonnet

symptom: target cmpw;bge A;b End;A: mr r24,r25;b End (result in pa reg r24); ours blt skip;mr;b
cause: plain if/empty-then/do-while/inline-void forms compile to baseline; ternary and inline-return max coalesce the result temp with ca (r25), emitting bge J;mr r25,r24;J: mr r24,r25 (6 diff lines but 96.1)
fix: failed: pa=ca>=pa?ca:pa, if(ca<pa){}else pa=ca, do{if(ca<pa)break;pa=ca;}while(0), pa=ca<pa?pa:ca, static inline mx(a,b), temp v at fn/loop top, void helper with early return, swapped operands, nested ternary, if(last<mid?ca>=pa:ca<pa) (84.9). Redundant-cond forms (else if (ca>=pa)) 97.0 but duplicate blt = pure steering, rejected (would need MATCH-PENDING R17 + ledger)
