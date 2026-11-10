# Anm lookups inside dont_inline: use macros that re-evaluate each use

- status: works
- tags: mwcc,dont_inline,macro

symptom: static-inline Lyt()/Anm() helpers become bl inside dont_inline; cached local gives 91.4%
cause: pragma blocks inline helpers; original reloads pointer each use
fix: macros expanding to static_cast<...>(self->objs[i]) at every use
