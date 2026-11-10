# fn_8033DB38 (RPBow_8033B690): colouring wall, sphere base pointer sj gets a top callee-saved reg in the original (r29) and the bottom in ours

- status: fails
- tags: RPBow_8033B690,fn_8033DB38,register,colouring,F6,wall
- scope: Pack/RPSports/RPBowScene/RPBow_8033B690
- source: orchestrator-1028

symptom: 96.0%: prologue li r28,0 (i byte-offset) vs ours li r29,0. Orig r29=sj (pj->sph), r28=i-off, r27=j-off, r23=si, r19=sj-iter; ours r29=i-off, r28=j-off, r19=si, r20=sj, r21=sj-iter. Plus a 48-line stack-slot/psq load-order shift in the ps_sub/ps_madd block after the 4th PSMTXMultVec (orig computes cpI-oI before cpJ-oJ)
cause: class 3: bl multiset (4 PSMTXMultVec, 2 fn_803281C4, 1 fn_8031617C, 2 sqrt), 750 lines and branch skeleton identical; allocation priority of sj above the index offsets is not source-visible
fix: failed: swap velJ = cpJ - oJ / velI = cpI - oI order (94.2), declare sj inline in the j-loop (identical), sj before si (95.9), const BowPinSphere* for si/sj (identical), permuter 8 min -j 6 base 2575 best 2570 noise with randomize_ast failures. Do not repeat. Likely needs a change that raises sj use count or live range above the index offsets.
