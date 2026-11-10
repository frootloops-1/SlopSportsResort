# E464 b340-e464j: preheader reload and e.a GPR levers exhausted

- status: fails
- tags: regalloc,schedule,b340,E464
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b340

symptom: retail issues lfs k, fsubs h, then base.y reload into f0; e[i].a coloured last (r8) as a var below i
cause: scheduler picks the base.y load (height 4) over k (height 2); IR optimizer removes any named e.a local before backend-00
fix: dead: CurPos&/CurPos*/f32[2]/f32* base in 120-480 orders; init-list and mkPos makers (37-46); base set in loop (47-49); named e.a in 7 types/any scope/declare-then-assign (34); offE/getAE/entry helpers (34-48); absDiff/absf. const SelView* v = self reload = same 34, no more honest than selBaseY. Next: mwcc_frontend_trace.py for which IR pass drops e.a. Trace: /private/tmp/scratch-b340-e464j/sched1
