# Callee-saved colouring wall: route a bool flag through a static inline helper (fn_8020A5F0 98.7 -> 100)

- status: works
- tags: regalloc,inline-helper,callee-saved,RPSports_8020a5f0
- scope: RPSports_8020a5f0

symptom: self r28 vs r29, flag r29 vs r26: flag vreg (degree 31) coloured before self
cause: named-local flag vreg is pushed late; an inline result vreg is numbered above the this-temps and pushed in the first simplify sweep
fix: static inline bool IsRelease(s32 cur, const s32& prev){bool ret=false; if(cur==0&&prev!=0) ret=true; return ret;} (const s32& so the load stays lazy; by value hoists it, 99.6). return a&&b / passing && into an inline param does not change colouring. R17 marker 101.
