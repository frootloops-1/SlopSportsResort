# Hand-new static inline (local p) moves a new'd object's colouring earlier

- status: works
- tags: regalloc,new,inline,RPBow_8031641C,inline-level
- source: RPBow_8031641C round 3

symptom: new'd object pointer coloured after an inline/accessor @-temp (wrong callee-saved reg order)
cause: inline-DECLARED locals get @-ids before every new temp and inline return temp; a plain new temp is numbered late
fix: static inline T* BowNewX(){ T* p=(T*)::operator new(sz); if(p){ctor body by hand} return p; } (R17). Declaring a ctor member local (u8* m) before p swaps their order. RPBow_8031641C: 80318EB0 225->23, 80316C7C 219->150 harness lines
