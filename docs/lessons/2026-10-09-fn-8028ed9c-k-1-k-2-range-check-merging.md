# fn_8028ED9C k==1||k==2 range-check merging

- status: works
- tags: RPGolCameraManager,bool,cmpwi

symptom: k==1||k==2 in an if() is merged into subi/cmplwi; if-chains 49-90%
cause: MWCC range-merges inline ||
fix: static inline bool isK12(k){return k==1||k==2;}; bool ret=true; if(!isK12(k)&&k!=5) ret=false; return ret; (gives li r3,1 + bnelr/beqlr)
