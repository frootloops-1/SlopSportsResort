# const-reference casts split loop induction registers for the same array element

- status: works
- tags: loop,induction,register,const,cse
- scope: Pack/RPUtility/RPUtlLytBase/fn_801C3574
- source: claude-opus

symptom: retail keeps separate callee-saved IVs for normalize src/dst and copy-store/transform-in of the same element; ours CSEs them (fewer savegpr)
cause: MWCC CSE treats address expressions reached through a const reference (operator const Vec*() const) as distinct from the plain lvalue
fix: static_cast<const T&>(a[i]) on the const-side uses (PSVECNormalize src, VEC3TransformNormal input); VEC3Normalize inline or reinterpret_cast pointers do NOT split. fn_801C3574 84.7 -> 96.8
