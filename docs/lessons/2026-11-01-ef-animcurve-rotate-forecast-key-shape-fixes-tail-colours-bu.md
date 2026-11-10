# ef_animcurve Rotate: forecast key shape fixes tail colours but score drops; forecast W/R random helpers regress

- status: fails
- tags: ef_animcurve,Rotate,forecast,dead-end
- scope: nw4r/ef/ef_animcurve
- source: claude/fc-animcurve-a

symptom: Rotate 99.1673/28 lines
cause: pKey/v0/k0=v0-12/v1/k1=v1-12/interp + flag0/flag1 locals gives target registers (k1 r7, v0 r6) but neg0 temp r9 vs r3 lets lbz flag1 hoist; dual hash add order + sign tmp unchanged
fix: dead: that shape 22 lines but 99.1 (<99.17); without flag locals 97.0/97.4; flags-then-bools 99.1; r0 right after k0 99.0; interp before v1 98.9; forecast GetRandomRangeW+R in dual branch 97.6, W only 97.7
