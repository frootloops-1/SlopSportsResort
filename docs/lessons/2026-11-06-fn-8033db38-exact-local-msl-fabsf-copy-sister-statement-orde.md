# fn_8033DB38 exact: local MSL fabsf copy + sister statement order (velI first, vr before vi/vj, n-first dots)

- status: works
- tags: fn_8033DB38,RPBow_8033B690,fabsf,fabs,MSL,cmath,statement-order,fpr,sister-function
- scope: Pack/RPSports/RPBowScene

symptom: fn_8033DB38 stuck at 97.4 with an exact I/J mirror in the velocity FPR block; fabsf from <cmath> gave 90.3
cause: the (float)fabs((double)x) inline boundary must come from a local copy of the MSL_SS/cmath bodies (real header changes codegen); the statement order must match the byte-exact sister fn_803395E4
fix: inline double fabs(double f){return __fabs(f);} inline float fabsf(float f){return (float)fabs((double)f);} at top of .cpp (97.4->98.0); then velI=cpI-oI; velJ=cpJ-oJ; rel=velJ-velI; vr=0.5f*Dot(&n,&rel); vi=fabsf(Dot(&n,&velI)); vj=fabsf(Dot(&n,&velJ)) (->100). velI-first alone (96.8) and n-first dots with velJ-first (95.5) both regress: the three changes only work together. Lesson: when a sister function matched, port its full shape at once, not piece by piece.
