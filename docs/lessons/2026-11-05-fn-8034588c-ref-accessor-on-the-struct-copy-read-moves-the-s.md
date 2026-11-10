# fn_8034588C: ref accessor on the struct-copy read moves the self+n*stride CSE to r0 (98.4 -> 99.0)

- status: open
- tags: inline-accessor,cse,regalloc,RPBow_803433E4
- scope: Pack/RPSports/RPBowScene/RPBow_803433E4

symptom: backend CSE add (IV+self) shared by stmt2/stmt3 gets r5 (retail r0); stmt3 xD0 load takes r0
cause: backend value numbering keeps the stmt2 vreg (r90, low), so stmt2/3 xD0 loads colour first and take r0; retail looks like an optimizer @temp CSE (colours before backend vregs)
fix: static inline BowPinMtx& BowLanePin(self,n){return self->lay[self->x14->xD0].pin[n];} for the m read only: 19 -> 9 (R17 256). Left: stmt3 m-source grouping (self+mulli)+IV vs retail mulli+(IV+self). Dead: self/n/lay-array holders (no change or worse), stmt1/stmt2 accessors (no effect), body accessors (13-26), pointer/value/n-first/local-in-inline accessor shapes (all 9 or worse), BowLanePins(self)[n] 19
