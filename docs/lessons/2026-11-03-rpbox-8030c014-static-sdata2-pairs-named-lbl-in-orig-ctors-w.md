# RPBox_8030c014: static sdata2 pairs named lbl_ in orig; .ctors word; extern const 1.0 literal

- status: works
- tags: sdata2,ctors,rpbox,symbol-name
- scope: Pack/RPSports/RPBoxScene/RPBox_8030c014

symptom: unit_cmp .ctors 0%, 3 sdata2 pair syms (lbl_804C5968/70/78) unmatched, extern lbl_804C5990 undefined in object
cause: source had static sFxBoth/Curve/Wave (names differ from symbols.txt lbl_), no .ctors word for hand sinit, and extern const f32 used where a plain 1.0f literal gives same code
fix: define extern const BoxPair lbl_804C5968/70/78 = {...} in place of the statics (+3 exact syms, no codegen change); force_active __declspec(section .ctors) ptr = fn_80311214 (.ctors 0->100); replace extern lbl_804C5990 by 1.0f except in fn_80310350 (regresses it 90.3->90.0). Remaining sdata2 97.35 = literals named lbl_ in orig only because unsplit refs them (59F4/59F8/5990/5A0C..), not fixable by source
