# fn_8034F53C (RPBow_8034E974): tail call (bctr) in last block keeps a dead trailing blr; 14 source shapes fail

- status: fails
- tags: RPBow_8034E974,fn_8034F53C,blr,tail-call,control-flow,F9
- scope: Pack/RPSports/RPBowScene/RPBow_8034E974
- source: orchestrator-1027

symptom: 99.89% text, fn 91.7%: ours 52 B vs target 48 B; extra blr after the bctr at 0x8034F568+0x30; early 'li r3,1' return is dup'd blr but the original epilogue block stays
cause: wall class 2 (control flow/return count): when the tail call is the last block CW keeps the dead trailing epilogue blr; when 'return true' is last the blr goes but layout becomes beq/call-first (65.8-82.5%)
fix: failed: if/else, early return, ||, ternary both orders, while(true), do-while(0), for(;;), switch, goto either way, static inline helper, BowSlot::Check() inline, #pragma peephole off, redundant 3-way if. Falling off the end of a non-void fn is compile error 10184. No other fn in the tree has 'blr ... bctr' without bl. Untried: real class member / header inline with different return-block structure.
