# Field loaded twice by original but CSE'd to one lwz: volatile read on the store source

- status: works
- tags: cse,volatile,load
- scope: RPBox
- source: claude

symptom: original: lwz r0,X then lwz r4,X (state read, then store source); ours one lwz
cause: CW CSEs the second read
fix: write the store source as *(volatile s32*)&self->f and read the other normally (fn_802DF174, fn_802E5BB8, fn_802FBCFC, fn_802FA794). Volatile on the first read gives swapped registers
