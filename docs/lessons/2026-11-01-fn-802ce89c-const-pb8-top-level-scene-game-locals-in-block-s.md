# fn_802CE89C: const pB8, top-level scene/game locals, in-block scene reload; 58 -> 26 lines

- status: open
- tags: constness,fn_802CE89C,colouring,R17,RPBox
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc
- source: constsweep 2026-11-01

symptom: 176 lines non-const pB8, 58 with const; M/p9C r5/r6 swap at top, case-1 join reload, case-5 scores register
cause: two CSE temps live across the switch coloured in the wrong order; target reloads M at the end of an if block
fix: named locals scene/game at top (game reused in case 5), scene = M at end of t==0 block (R17 row 48), (scores+bCC)[12]; left: case-0 SetScore block r5/r6 swap (back-end temps), case-1 white GXColor at sp+0xc vs shared sp+8 (MWCC never shares slots between disjoint same-type aggregate locals)
