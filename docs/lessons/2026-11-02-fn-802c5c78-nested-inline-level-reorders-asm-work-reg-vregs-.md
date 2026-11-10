# fn_802C5C78: nested inline level reorders asm work-reg vregs vs following inline params

- status: works
- tags: fpr,colouring,inline,asm,vec3lerp,RPGol_802c58d4
- scope: Pack/RPSports/RPGolScene/RPGol_802c58d4
- source: opus pass 4

symptom: VEC3Lerp work regs coloured before the next statement's golLerpB params (ours w0 f2/w1 f3, target f10/f4) while t must stay f1
cause: inline vars numbered in reverse expansion order; a nested inline level is expanded later so its locals get lower vregs than the following statement's inline params, the outer param t stays higher
fix: static inline golVecLerpW(out,a,b,t){ nw4r::math::VEC3Lerp(...); } keeping source order VecLerp then tmp.y = f7C + golLerpB(...) (MATCH-PENDING R17)
