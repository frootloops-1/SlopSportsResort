# Right-to-left arg evaluation fixes load order: t.set(m._03,m._13,m._23) and madd helper

- status: works
- tags: mwcc,scheduling,fp
- scope: RPTns_8023c74c
- source: claude/rptns-2

symptom: loads z,y,x but stores x,y,z; fmadds with operand A loaded second
cause: MWCC evaluates call args right to left
fix: use an inline set(x,y,z) for the vector; static inline void Madd(f32& d,f32 a,f32 s){d=a*s+d;} called per component
