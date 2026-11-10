# x * 64.0f literal canonicalises to fmuls K,x; a method taking the scale as a parameter keeps x first

- status: works
- tags: mwcc,operand-order,literal
- scope: Pack/RPUtility/RPUtl_801C73B0
- source: claude/rputl-c67b8-1027

symptom: fn_801C7E80 exact with extern const lbl, 99.1 after switching to the literal
cause: literal operands are moved first in commutative fmuls; an inline param is a variable and keeps source order
fix: Record::pack(const Quaternion& q, const Vector& t, f32 scale) { x = (s16)(t.x * scale); ... } called with 64.0f
