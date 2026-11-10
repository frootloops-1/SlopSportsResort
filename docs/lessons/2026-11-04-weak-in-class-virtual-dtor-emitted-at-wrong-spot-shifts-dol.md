# Weak in-class virtual dtor emitted at wrong spot shifts DOL

- status: works
- tags: dtor,weak,emission-order,flip
- scope: RPSportsCommon/RPSports_80211b60
- source: claude/sp80211-1104 82ddd20e8

symptom: Unit 100% in objdiff but flip_gate FLIP-FAIL 121-byte DOL diff: weak inline dtor placed after a later function
cause: Inline-defined virtual dtor is emitted at its first-use point, not where retail has it
fix: Declare dtor in class, define it out of line at the retail position in the TU
