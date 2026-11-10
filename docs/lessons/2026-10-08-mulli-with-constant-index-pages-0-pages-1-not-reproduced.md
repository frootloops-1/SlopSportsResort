# mulli with constant index (pages[0]/pages[1]) not reproduced

- status: fails
- tags: mulli,constant-index

symptom: orig keeps 'li r6,0; mulli r7,r6,0x18' but ours folds offsets
cause: unknown; tried s32 type=0/1 locals, in-class inline helpers, static helpers, 2-iter loop with if(i==0), type++ between inlines
fix: open (fn_801E2970, 82.4%); needs condition-derived/phi index
