# Inline helper boundary moves temporaries to the end of the stack frame

- status: works
- tags: mwcc,frame,stack-slot,inline-helper
- source: RPUtl_801C9E7C

symptom: Descriptor/MTX temps of one block at wrong frame offsets (target has them lowest)
cause: temps created inside an inlined helper are allocated after the caller's own temps
fix: wrap the block (Descriptor target; target.set(pane); strcmp) and getPrevious().valid in Cursor inline helpers: fn_801CA3DC 64 -> 90
