# fn_802023B0: msg vs idx*12 CSE r30/r31 swap closed by inline getter (late vreg)

- status: works
- tags: colouring,vreg,inline-helper,RPSports_80201240,R17
- scope: Pack/RPSports/RPSportsCommon/RPSports_80201240

symptom: named msg (vreg 39) coloured after the idx*12 CSE temp (vreg 42) -> r30 instead of r31
cause: colour_sim: ascending sweep pushes the lower vreg first, so the higher-numbered temp is coloured first
fix: static inline SpResetMsg() returning *(void**)(lbl_804BF730+0x60); msg = SpResetMsg(); -> 99.5 -> 100 (MATCH-PENDING R17, ledger row 35). Direct ((void**)p)[0x18] spelling: no change.
