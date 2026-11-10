# TU-wide force_active emits dead static inline helpers

- status: fails
- tags: force_active,deadstrip,inline
- scope: RPBoxScene
- source: RPBox_802fe93c

symptom: flip DOL +140 bytes: an unused static inline (BoxRandSign) emitted out of line
cause: #pragma force_active on at file scope also forces otherwise-dropped functions
fix: wrap only the base+offset tables/statics in #pragma push / force_active on / pop
