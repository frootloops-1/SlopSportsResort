# lyt_material Material ctor: u32-arithmetic GetTexCoordGenAry fixes inlined CSE add association

- status: works
- tags: lyt_material,nw4r,ctor,inline,cse,add-order,reassociation,match-pending
- scope: nw4r/lyt/lyt_material
- source: session 2026-10-26 opus

symptom: Inlined getter shared (CSE) by two inline expansions emits base+(A+B); retail (base+A)+B. Standalone getter already linearized.
cause: Diagnosed: removing the second (SetTexCoordGenNum) expansion makes the ctor copy reassociate, so CSE of the grouped A+B blocks linearisation when the base add is u8* pointer arithmetic. With integer (u32) base+offset the tree linearises before CSE and the whole pointer is shared.
fix: Write that one getter as reinterpret_cast<T*>(reinterpret_cast<u32>(mpGXMem) + CalcOffset...(mGXMemCap)): 21/21 exact. Changing detail::ConvertOffsToPtr (either overload) to u32 regresses 5 lyt_material fns (ReserveGXMem, GetIndTexSRTAry, SetColorElement, SetupGX, ctor); other lyt units unaffected. No-ops: inline on CalcOffset*, non-const getter via const_cast of const getter, uninitialised pTexCoordGen declared at top. int return type of CalcOffsetTexCoordGenAry regresses. Flagged MATCH-PENDING (R17).
