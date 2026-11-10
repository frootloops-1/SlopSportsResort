# RPBox cf93c D235C: genuine virtual other->v40(2) gives r12 but loses lwz-before-li ordering (99.8 -> 96.6)

- status: fails
- tags: RPBox,cf93c,fn_802D235C,virtual,scheduler,mwcc_dbg
- scope: RPBox_802cf93c

symptom: fn_802D235C vptr load: target lwz r12,0x144(r4); mr r3,r4; li r4,2; ours (manual HitFn table) lwz r5 then lwz r12,0x40(r5)
cause: A real virtual call is emitted as mr r3,other; li r4,2; lwz r12,r3,0x144 and the prepass scheduler keeps that order, so the post-RA peephole cannot forward r4 into the lwz (li r4 clobbers it) and the lwz stays after li. Target needs lwz before li in the pre-RA stream.
fix: No source found. other->v40(2) direct, BOOL hit local, int kind=2, BoxObj* o alias, BoxObj* const cast all give the same 96.6 (r12 right, order wrong); manual table keeps 99.83. Needs something that makes the scheduler place the vptr lwz before li r4.
