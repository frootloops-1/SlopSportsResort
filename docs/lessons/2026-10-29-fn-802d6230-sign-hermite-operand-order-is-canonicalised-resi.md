# fn_802D6230: sign*Hermite operand order is canonicalised; residue is FPR colouring of |f48| (f9 vs f12)

- status: open
- tags: fn_802D6230,RPBox_802cf93c,fpr
- scope: RPBox_802cf93c

symptom: 102 diff lines in the BoxVec3 V(...) Hermite block: f9/f10/f11 vs f12/f9/f10 rotation (99.2)
cause: colouring of the early fabs(cc->f48) value that lives across the f4C sign branch
fix: failed: (cond ? 1 : -1) * BoxHermite2(...) instead of Hermite * (cond ? ...) (identical output). also f32 ay = BoxFAbs(cc->f48) named local (99.1, 118 lines)
