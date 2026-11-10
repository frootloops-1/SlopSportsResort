# fn_802030CC: offset IV and PMF temp slot direction need a REAL out-of-line ctor; inlined (placement new) adds null check

- status: open
- tags: ctor,ptmf,stack,induction,RPSports_80201240
- scope: Pack/RPSports/RPSportsCommon/RPSports_80201240
- source: claude/sp80201-1104

symptom: fx loop pointer IV (mr r21,r30) vs retail add r4,r30,r21; PMF arg temps ascending vs retail descending
cause: only a real ctor of a class with members having virtual dtors gives offset IVs and descending temp slots; placement new keeps IV but adds cmpwi/beq; direct body / auto-inlined static init helper / const-ref / functional-cast PMF args do not change slots
fix: out-of-line SpSelCtor::SpSelCtor() reaches 380/380 insns with retail slot order; remaining li -1/PMF scheduling. Needs fn_802030CC renamed to __ct__ (Matching 801ee354 calls fn_802030CC: orchestrator)
