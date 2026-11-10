# Struct-copy loop at 98.8%: pass copied struct by value (RPGolMapObjBase)

- status: works
- tags: golf,loop,unroll,byvalue,RPGolMapObjBase
- scope: RPGolMapObjBase
- source: opus

symptom: unrolled loop counter addi one slot early (98.8) with const T*/const T& item
cause: scheduling differs by param kind
fix: item as by-value struct param; dst = e->items + idx temp; direct dst->v[k]=item.v[k] (struct temps into s16 switch to 4x unroll); dead ends: ++i, i+=1, n>i, while, &items[idx], idx<<3, u16 n(94.9), whole-loop inline (97.6)
