# RPBox_802c7924 sdata2: half-angle temp orders 0.5f before 40.74f

- status: works
- tags: sdata2,pool-order,literal,RPBox_802c7924
- scope: Pack/RPSports/RPBoxScene/RPBox_802c7924
- source: claude/z-boxsd2-1029

symptom: two adjacent .sdata2 floats swapped (40.743664f before 0.5f) in 40.743664f * (0.5f * (t * angle)); code identical, DOL diff only sda21 displacement bytes
cause: pool literals are created in expression-tree pre-order (outer left constant first), not load order; a static inline wrapper does not help because single-use args are substituted
fix: f32 half = 0.5f * (t * angle); SinCosFIdx(&s, &c, 40.743664f * half); (no marker; same code)
