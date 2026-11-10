# fn_8021CC18 closed: dead local-array store of -1.0f before the compare fixes hoisted-constant FPR order

- status: works
- tags: RPTnsScene,regalloc,fpr,hoisted-constant,MATCH-PENDING
- scope: Pack/RPSports/RPTnsScene/RPTns_8021ba24 fn_8021CC18
- source: claude/tns-cc18-1103

symptom: hoisted loop constants 0.0f (first compare) and -1.0f (conditional stores) swapped f27/f28; fpr_replay search: 0.0f vreg must be numbered after -1.0f
cause: backend float constants get vregs in codegen order; the compare's 0.0f is codegen'd before the then-block's -1.0f. Named locals/inline returns holding -1.0f become variables (f32-f45) that are late-sweep and take f31; constant inline args are propagated (no effect)
fix: f32 dummy[1]; dummy[0] = -1.0f; right before the if: frontend keeps the array store, so -1.0f is materialised first, backend then deletes the dead store -> 100. A dead '0.0f;' literal statement before it keeps .sdata2 order (else 100 -> 96). Failed: named neg in/out of loop, inline TnsFlipSign()/TnsFlipRot(s) helpers, '< 0.0' double, chain assign, x*-1.0f in tnsCopyFlip, dead store to rot.m[8] before copy (store survives). while(c){...;break;} fixes FPR but changes layout (body-first codegen)
