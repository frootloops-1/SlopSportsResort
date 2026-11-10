# (idx-5) folded into table disp: use local s32 i = idx-5

- status: works
- tags: mwcc,index,offset-folding

symptom: slwi only, no subi
cause: constant folding into table base
fix: local i = idx - 5 then names[i]
