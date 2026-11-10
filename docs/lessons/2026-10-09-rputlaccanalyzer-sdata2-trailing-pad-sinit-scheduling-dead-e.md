# RPUtlAccAnalyzer sdata2 trailing pad / sinit scheduling dead ends

- status: fails
- tags: sdata2,sinit,scheduling

symptom: sdata2 4B short; sinit GREEN+2 load hoisted in orig
cause: unknown; trailing zero likely alignment pad
fix: tried: const f32 tail var (worse, reorders pool 80%); sinit: ctor body assigns, padding(0) init, swapping vector/colors order, ColorTable wrapper with c[i]=... all worse or equal
