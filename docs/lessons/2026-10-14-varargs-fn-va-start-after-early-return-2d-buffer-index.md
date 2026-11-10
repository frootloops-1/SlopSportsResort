# Varargs fn: va_start after early return; 2D buffer index

- status: works
- tags: varargs,arrays
- scope: RPGolScene
- source: claude/rpgol-small

symptom: fn_802AADEC 88.8% with pointer math; va_list built too early
cause: original builds va_list only on slow path; +4 offset hoisted with raw pointer math
fix: va_start after the early return; char e[0x20][0x30]; return self->e[self->count++]; stdarg.h is safe in these TUs
