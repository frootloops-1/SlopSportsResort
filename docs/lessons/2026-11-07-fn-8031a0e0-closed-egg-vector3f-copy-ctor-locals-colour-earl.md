# fn_8031A0E0 closed: EGG::Vector3f copy-ctor locals colour early; plain VEC3 + assignment fixes block FPRs

- status: works
- tags: A0E0,RPBow,fpr,regalloc,Vector3f,copy
- scope: fn_8031A0E0
- source: round 11

symptom: P/Q block: Q-ctor v1BC loads took f7/f8 (retail f2-f4), fk pushed to f9, schedule differs
cause: EGG::Vector3f Q(self->v1BC) inlines Vector3f(const VEC3&) whose copied values get low vreg numbers coloured before block temps
fix: VEC3 Q; Q = self->v1BC; (struct assignment) -> ordinary temps; with rz row pointer (R17 399) and h[1] (R17 400) fn exact
