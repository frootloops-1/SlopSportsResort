# u32 index picks the u32 overload; target calls the int overload: cast (int)

- status: works
- tags: overload,GetResNode,GetResShp,cast,int,u32
- scope: RPGrpModelG3D
- source: sonnet worker, verified 2026-10-12

symptom: 99.8-99.9% near-miss; only difference is a call symbol (...FUl vs ...Fi)
cause: Overloaded GetResNode/GetResShp(u32) vs (int); passing u32 idx binds the u32 one
fix: Cast the argument to (int) at the call site (also in inline header copies)
