# Overloaded weak virtual order: give one overload its own member name, declared in target position

- status: works
- tags: weak,order,overload,GetWorldMtx,RPGrpModelG3D
- scope: Pack/RPGraphics/RPGrpModelImplement

symptom: Target weak run GetWorldMtx(UsP),ReferWorldMtx,GetWorldMtx(Us) unreachable: MWCC groups overloads of one name together
cause: weak inline members emitted by member name in first-declaration order, overloads reverse order
fix: Rename slot 0x40 (const MTX34*(u16)) to its own name (GetWorldMtxPtr, inferred) in RPGrpModel/G3D/Rfl headers + symbols.txt, declare it after ReferWorldMtx in the derived class: DOL 0 bytes
