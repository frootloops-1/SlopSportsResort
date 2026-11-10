# if(e) e=(T*)ctor(e) avoids extra mr after __nw__

- status: works
- tags: mwcc,new,ctor
- scope: RPGol_802b66c4
- source: sonnet-worker

symptom: extra mr r31,r3
cause: void ctor declaration
fix: declare ctor returning T* and assign
