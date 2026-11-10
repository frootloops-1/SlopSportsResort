# Sub-object at raw offset: use a view struct field, not (T*)((u8*)self+off)

- status: works
- tags: cse,offset,view-struct,mwcc
- source: RPBox_802cf93c 2026-10-23

symptom: addi rX,self,off hoisted into a saved reg and fields addressed as 0x34(rX); orig uses 0x23c(self) per access (91.1/96.9%)
cause: pointer-arithmetic casts are CSE'd into one base register; member access folds the offset into each load/store
fix: struct V{u8 pad[off]; Sub s;}; use &((V*)self)->s at each use (fn_802D5DE0, fn_802D5B3C -> 100)
