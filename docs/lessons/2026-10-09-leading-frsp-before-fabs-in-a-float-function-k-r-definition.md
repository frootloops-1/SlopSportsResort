# Leading frsp before fabs in a float function: K&R definition

- status: works
- tags: msl,fabsf,knr
- scope: float functions with leading frsp
- source: claude/msl-text math_float 2026-10-09

symptom: ANSI float fabsf gives fabs;frsp (71%) but original is frsp;fabs;frsp
cause: original defined K&R style 'float fabsf(x) float x;' so the arg is promoted to double and rounded on entry
fix: float fabsf(x) float x; { return (float)fabs_wrapper(x); } with inline double wrapper around __fabs; math.h must not be included (prototype conflict)
