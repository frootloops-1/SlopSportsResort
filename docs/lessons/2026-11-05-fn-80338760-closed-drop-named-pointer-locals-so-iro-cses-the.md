# fn_80338760 closed: drop named pointer locals so IRO CSEs the load into @vars (r19/r20 order)

- status: works
- tags: colouring,named-local,iro,cse,RPBow_803381DC
- scope: Pack/RPSports/RPBowScene/RPBow_803381DC

symptom: late inline param (SE manager) and first ball pointer got r20/r19 swapped vs retail
cause: named ball/triBall (= self->mpBall) colour after all @vars; retail has them as IRO CSE @vars, so triBall hands out r19 before the SE manager is coloured
fix: write self->mpBall->GetPos()/->mRadius directly in both calls (no BowBall* locals): 6 -> 0. mwcc_dbg dump showed the colouring order; harness confirmed
