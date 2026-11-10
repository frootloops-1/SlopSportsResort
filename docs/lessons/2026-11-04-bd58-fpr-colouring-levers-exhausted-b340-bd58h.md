# BD58 FPR colouring levers exhausted (b340-bd58h)

- status: fails
- tags: regalloc,declaration-order,b340,BD58
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b340

symptom: retail L f0 first, t2 f1 before t1 f2; ours t1/t2 always first
cause: t1/t2 named vars outrank L in colouring; L never picked early
fix: dead: lerp arithmetic forms (same code), selLerp/selLerpV param perms, 36 t0/t1/t2 orders, t as inline expr/s32 inline/int locals, selClamp or unrolled clamp, const/SelPt3* selLerpAll, named z=-120, L named/param
