# Inline bool taking object pointer gives li r0,1;cmp;beq;cmp;beq;li r0,0

- status: works
- tags: mwcc,inline,branch
- source: RPGol_802b90b4

symptom: branch shape inverted
cause: inline took the value instead of the pointer
fix: inline bool f(T* o){return o->x==3||o->x==0;}
