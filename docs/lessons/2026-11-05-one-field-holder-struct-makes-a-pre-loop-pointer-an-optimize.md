# One-field holder struct makes a pre-loop pointer an optimizer temp numbered after loop source temps

- status: works
- tags: regalloc,colouring,holder,scalarize,fn_80318EB0,RPBow_8031641C
- scope: Pack/RPSports/RPBowScene/RPBow_8031641C

symptom: named pointer local defined before a loop colours below all @temps (r24); retail colours it between the loop's call-return temp and the LICM temps
cause: IRO_ScalarizeClassDataMembers creates the scalarized field temp at optimizer time: after all source-order temps, before LICM/strength-reduction temps
fix: struct BowDbRef { T* p; }; BowDbRef v; v.p = new ... / v.p = 0; use v.p (R17). fn_80318EB0 99.9 -> 100 (harness 23 -> 0), RPBow_8031641C flipped Matching. Same lever as BowSphRef (RPBow_8033B690).
