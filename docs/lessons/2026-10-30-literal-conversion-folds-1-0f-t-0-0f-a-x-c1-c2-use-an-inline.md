# Literal conversion folds 1.0f*t / 0.0f*a / x*(c1*c2): use an inline lerp / real header inline (mFovY/2.0f) to keep the multiply

- status: works
- tags: sdata2,literal,fold,inline,float
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c
- source: claude/d1f1d4c-b-1031

symptom: after replacing extern const f32 lbl_ with literals, fn_801F2B30/31C4 lost fmuls 1.0*ratio (97%), 469C lost 0*a, SetFovy(45) folded 0.711*(45*0.5) into a new 16.0f literal
cause: MWCC folds literal arithmetic in one expression; an inline function parameter (b in a*(1-t)+b*t) or a member re-read (mFovY/2.0f, as in eggFrustum.h SetFovy) is not folded
fix: inline f32 SpLerp(a,b,t){return a*(1.0f-t)+b*t;} for 1.0/255 lerps; Frustum::SetFovy written as the real header (early return, assert, mFovy=fovy, SinCosDeg(mFovy/2.0f)); x/2.0f instead of x*0.5f fixed the fmuls operand order
