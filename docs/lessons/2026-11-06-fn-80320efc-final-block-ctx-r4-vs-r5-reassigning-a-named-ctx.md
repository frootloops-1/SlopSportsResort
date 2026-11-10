# fn_80320EFC final-block ctx r4 vs r5: reassigning a named ctx does not merge webs

- status: fails
- tags: RPBow_80320EFC,fn_80320EFC,gpr
- scope: fn_80320EFC

symptom: retail loads self->x518 into r5 both before and after the sprintf; ours r4 then r5
cause: unknown; ours has two IRO vars (@719, @721), the first one only conflicts with r0/r3 temps
fix: none. Dead: ctx = self->x518 reassigned for BowRatio (block or function scope, const or non-const), const ctx, ctx before outer if, swapped compare, int cur, g pointer, Set(const&), struct copy
