# Do-while pointer loop bound without end variable

- status: works
- tags: loop,unroll
- source: RPTns_80216810

symptom: Loop bound lands in wrong register
cause: Extra end variable changes hoisting
fix: Compare against &self->elems[0] directly; do-while over s32* p with p/i declaration order varying per function
