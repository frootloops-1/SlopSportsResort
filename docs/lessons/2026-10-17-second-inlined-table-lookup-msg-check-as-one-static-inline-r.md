# second inlined table lookup + msg check as one static inline returning the msg

- status: works
- tags: regalloc,inline,rpbsb
- source: RPBsb_80273950 2026-10-17

symptom: fn_80273F24 99.4: entry ptr and msg ptr in r5/r6 swapped after two inlined lookups
cause: orig wrapped lookup+GetMsg in an inline returning the msg pointer
fix: static inline const wchar_t* GetMsg(self,key){e=Find(key); m=NULL; if(e->group||e->index) m=GetMsg(..); return m;} then if (GetMsg(self,key)!=NULL)
