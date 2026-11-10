# fn_802CF94C: lerp v as repeated expression + named p closes FPR, 28 -> 10 lines; owner/w3D4 colour order still open

- status: open
- tags: fn_802CF94C,RPBox_802cf93c,regalloc,mwcc_dbg
- scope: RPBox_802cf93c

symptom: case 8: owner r7/w3D4 r5 vs target r5/r6; lerp FPR v f5 vs f2
cause: named v/from/to are coloured after all temps; writing (u - 2.0f) twice gives a late codegen temp coloured early (v=f2). For GPR: owner is a front-end @ temp, w3D4 a codegen temp (coloured first). Q3 proved the fix: if w3D4 is also an @ temp created after owner (w3D4 repeated in a non-foldable expression, e.g. 'w < 0 ? 0 : w') registers match, but that adds srawi/andc
fix: kept: f50 = from*(1.0f-(u-2.0f)) + to*(u-2.0f) with named from/to; BoxObj** p declared at function top, p = owner->pl; p += owner->w3D4. Failed to duplicate w3D4 without code: x|x, x&x, x-x, x==x?x:0, same-arm ternaries, (void)w, dead local, call expr thrice, x*1 arms. Untried: a real second use of the player-kind pointer that costs no instruction
