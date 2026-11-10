# fn_8033DB38 97.4: inline impulse weights + dot operand/stmt order (+1.0); velocity block is an exact I/J mirror

- status: open
- tags: fn_8033DB38,RPBow,scheduler,phase1,fpr,regalloc
- scope: Pack/RPSports/RPBowScene/RPBow_8033B690
- source: claude/bow-8033B690-1105 c3eb9b49e

symptom: 96.4 velocity-block wall
cause: Phase-1 (post-RA) heights decide the z-load tie: second-evaluated sub wins because its z copy runs through f0 into the critical vi dot. Current J-first source is an exact mirror of retail incl. stack slots (retail evaluates I first, I temp at 0xa4). I-first sources lose the mirror since rel=velJ-velI and the vi compare are asymmetric.
fix: Wins: impI = n*imp*(vj/(vi+vj)), impJ = -n*imp*(vi/(vi+vj)) without wi/wj locals (96.7->97.4); vi=fabs(Dot(&velI,&n)), vr=0.5*Dot(&rel,&n) before vj=fabs(Dot(&n,&velJ)), imp before weights (96.4->96.7). Dead (objdiff-scored): 1440 combos of 30 stmt orders x 8 dot operand orders x 6 wi/wj/imp orders, imp before clamps (93), sum local, impJ before impI, nn=-n, n*(imp*w), BowSet2 arg-order helper (decouples temp slot from eval order but 95.8/96.1), const-ref/named temps tI/tJ, f32 one-field holders on vi/vj/vr/imp. fn_harness diff count disagrees with objdiff (61 lines = 95.7%): rank with verify.py.
