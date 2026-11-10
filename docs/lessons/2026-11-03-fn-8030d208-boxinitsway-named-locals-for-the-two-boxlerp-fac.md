# fn_8030D208 BoxInitSway: named locals for the two BoxLerp factors fix f7/f10 jitter-vs-lerp swap

- status: works
- tags: regalloc,float,locals
- scope: Pack/RPSports/RPBoxScene/RPBox_8030c014

symptom: fmadds/fdivs result registers f7/f10 swapped in fA0 = scale*Lerp*Lerp*jitter
cause: single chained expression colours jitter before lerp
fix: f32 l1=BoxLerp(..col); f32 l2=BoxLerp(..tint); fA0 = scale*l1*l2*jitter; remaining: fmuls operand order and a/speed f2/f5 swap (tried a/speed order, sign*lerp order, no change)
