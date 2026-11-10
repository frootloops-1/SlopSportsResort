# b340: selLerp by-reference + selUpdate helper lifts DED4 57.9->91.4 but costs BD58

- status: works
- tags: helper,inline,selLerp,b340,DED4,BD58
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b340

symptom: DED4 stuck 57.9 with value selLerp; BD58 91.4 FPR colouring
cause: shared selLerp shape trades between DED4 and BD58
fix: selLerp(const f32& a,const f32& b,f32 t) no d local, selLerpV x,y,z order, selUpdate(SelClampArgs*,SelView*) in DED4: DED4 91.4, unit .text 95.77->97.75, BD58 89.5 (keep its named-t body; selUpdate in BD58 86.7). Patch /private/tmp/scratch-b340-bd58h/ded4_selupdate.patch. Harness count and objdiff disagree for BD58 (70 diffs vs 90.3): check with verify.py
