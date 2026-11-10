# fn_80339E5C: count via inline helper return + radii[m] + v2954 ref first closes IRO var order

- status: works
- tags: RPBow_803381DC,fn_80339E5C,iro,iv,regalloc,inline-helper
- scope: Pack/RPSports/RPBowScene

symptom: loop bound (m==0)+1 CSE'd into a late IRO @var (r23) and radii offset a backend SR temp (r31); retail reversed (count r30, offset IV r23)
cause: radii[sample] copy blocks IRO SR of m*4; radius read before v2954 makes the offset IV precede the v2954 IV; an inline-helper return value for count is not an IRO @var
fix: int count = BowWallContactCount(m) (static inline (index==0)+1, R17 251); mpRadii[m] without sample; const VEC3& c = BowAsVec(v2954[m]) before f32 r = mpRadii[m]. 99.9 -> 100. Named int count alone = 45 harness diffs, count holder struct = 18.
