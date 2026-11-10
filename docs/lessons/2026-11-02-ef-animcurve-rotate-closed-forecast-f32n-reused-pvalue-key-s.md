# ef_animcurve Rotate closed: forecast F32N reused pValue key shape + GetRandomRangeStride hash order

- status: works
- tags: ef_animcurve,rotate,forecast,scheduling
- scope: nw4r/ef/ef_animcurve AnimCurveExecuteRotate
- source: claude/codex-fc2-animcurve-rot

symptom: Rotate 99.17/28 lines: tail key setup (k1 r11, neg0 temp, v0 sunk), dual-hash add operand order x2, sign temp lbz r0 vs r5
cause: hash: term order seed*A+hdr*B+idx*D+loop*C+K (GetRandomRangeStride form) gives add(loop*C, S). sign temp: random0 copy placement. tail: a single reused pValue variable (pValue=pKey->v; v0=pValue; k0=pValue-12; pValue=keys[idx+1].v; v1=pValue; k1=pValue-12) keeps flag loads through value pointers so pre-RA order matches; plain U8-style v1/k1 folds and hoists lbz flag1
fix: RotRandom helper (union, GetRandomRangeStride term order) for both dual hashes: 99.1862; 'u32 random0 = rangeRandom0;' moved before U8Select (from permuter state): 99.38; forecast F32N pValue-reuse key block with flag0/flag1 locals then bools, interp from pKey: 100. Dead: interp derived from pValue-12 (subi, 98.97), dropping flag locals (branch shape moves), pKey1 named second key (=U8-style 99.35), regsearch generic 10 min (objdiff 99.15, touches U8/F32)
