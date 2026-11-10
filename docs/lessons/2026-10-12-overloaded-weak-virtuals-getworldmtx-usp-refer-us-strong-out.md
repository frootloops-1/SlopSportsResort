# Overloaded weak virtuals GetWorldMtx(UsP)/Refer/Us: strong out-of-class defs move them before the weak group (wrong)

- status: fails
- tags: weak,order,overload,GetWorldMtx,out-of-class,RPGrpModelG3D,layout
- scope: RPGrpModelImplement

symptom: Target weak run is GetKind,SetCallbackJointIndex,GetCallbackJointIndex,VF_0x8,VF_0x10,VF_0xC,GetWorldMtx(UsP),ReferWorldMtx,GetWorldMtx(Us),GetViewMtx...; ours groups overloads (UsP,Us,Refer)
cause: MWCC groups weak overloads under one name at the first declaration
fix: open. Tried: declaration permutations (3), Us out-of-class inline, and all three as strong .cpp definitions (strong funcs are emitted before the weak run: 405 DOL bytes instead of 276). Same pattern exists in RPGrpModelRfl (weak order UsP, Refer, Us)

O1 (Opus, 2026-10-15, claude/nm-weak-1), dead end: MWCC emits weak inline members by member NAME in first-declaration order, all overloads of a name together at that point in REVERSE declaration order (UsP,Us -> Us,UsP; GetViewMtx P,UsP -> UsP,P). Out-of-class inline bodies in any order, declaring UsP,Refer,Us, and `using RPGrpModel::GetWorldMtx;` between them change nothing (still 276 bytes). The class-template rule does not apply (virtuals cannot be member templates; templating the class changes mangling). UsP,Refer,Us is unreachable with one overload set. Lead (unchecked): the target order is what a non-overloaded name for slot 0x40 gives; the weak names are inferred, so the real 0x40 name may differ (symbols.txt + header rename in RPGrpModel/G3D/Rfl).
