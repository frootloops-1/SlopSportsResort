# fn_802D235C permuter 10 min -j2 (~900 iters): no candidate beats base; virtual-call form variants all 96.6

- status: fails
- tags: permuter,vcall,rpbox,fn_802D235C
- scope: fn_802D235C
- source: claude/pm3-1028

symptom: retail lwz r12,0x144(r4) before mr r3,r4; ours lwz r5 / lwz r12,0x40(r5) (99.8, 4 lines); real virtual gives mr/li then lwz r12,0x144(r3) (96.6)
cause: mwcc vcall lowering loads vptr via the copied this arg r3; copy-prop to r4 is blocked because li r4,2 clobbers r4; self->v38(n) case works because self lives in r30. Permuter stand-in also hit 'undefined struct BoxObj' on ~50% of candidates (virtual members unknown to the C parser)
fix: failed: permute.py setup --keep-bodies --static, run 10 min -j2: base score 10, best 10, ~900 iters, no tie state kept; other->v40(2)!=0 and negated-branch forms all 96.6. Park.
