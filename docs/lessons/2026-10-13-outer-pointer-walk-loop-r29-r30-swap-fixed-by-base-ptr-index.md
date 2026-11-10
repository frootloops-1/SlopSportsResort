# Outer pointer-walk loop r29/r30 swap fixed by base ptr + index

- status: works
- tags: mwcc,regalloc,loop
- scope: RPGol_802bf4f8
- source: opus-worker

symptom: fn_802C087C nested loop: outer c++ pointer and inner stwu ptr swapped
cause: pointer-increment form changes IV allocation
fix: T* c = self->cell; plain i loop indexing c[i].field (no c++); self->cell[i] directly gives wrong base offsets
