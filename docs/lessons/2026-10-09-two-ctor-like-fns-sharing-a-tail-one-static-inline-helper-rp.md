# Two ctor-like fns sharing a tail -> one static inline helper (RPGolMapObjBase)

- status: works
- tags: golf,inline,ctor,RPGolMapObjBase
- scope: RPGolMapObjBase
- source: sonnet

symptom: fn_80290778 = fn_80290658 call + tail, fn_802908E8 = tail only, frames 0x60 vs 0x50
cause: shared tail
fix: static inline CreateModel(self,args) called from both; Construct(a,b,c,e,d) stack args swapped; plain switch 0->2,1->0,2->1
