# Pool order 128/pi before 2pi: SinCosFIdx(NW4R_MATH_RAD_TO_FIDX(2*PI*x)) not SinCosRad(2*PI*x)

- status: works
- tags: egg,nw4r,math,pool,sdata2,SinCos
- scope: egg/gfxe/eggPostEffectBlur
- source: claude

symptom: sdata2 has 40.743664 then 6.2831855; SinCosRad(&s,&c,2*PI*x) pools 2pi first
cause: inline param evaluated (2pi created) before the body's RAD_TO_FIDX constant; the macro inline in the arg creates 128/pi first
fix: math::SinCosFIdx(&s, &c, NW4R_MATH_RAD_TO_FIDX(2 * NW4R_MATH_PI * (...)))
