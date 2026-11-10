# -inline deferred: write TU in reverse address order; vptr sits at first virtual declaration (declare virtual dtor after data members)

- status: works
- tags: order,deferred,vptr,layout,virtual,RPGrpModelManager,weak
- scope: RPGrpModelManager
- source: sonnet worker 2026-10-12

symptom: Functions emitted in wrong order; fields shifted by 4 when the dtor was declared first
cause: cflags -inline deferred emits functions in reverse source order; MWCC puts vptr where the first virtual is declared; in-class inline functions land after all regular ones in the weak group
fix: Define functions from highest to lowest address; declare virtual dtor after data members; loop reg swap fixed by int i=0; T** pp=array; for(;i<8;i++,pp++)
