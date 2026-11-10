# Nested sprintf/findTextBox pointer loop r29/r30 swap (fn_802C087C)

- status: open
- tags: golf,regalloc,loop
- scope: RPGol_802bf4f8
- source: sonnet-worker

symptom: 98.7%: outer cell ptr r30 / inner stwu ptr r29 swapped
cause: unknown; same form matches fn_802C0810 single loop
fix: failed: end-of-body c++, do/while, *t++, hoisted i/j, &self->cell[i], local RPSysLayout*; candidate for permuter
