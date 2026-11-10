# fn_80221664 (RPTns_80220994) hard tier: original is very likely a real C++ ctor; opt_common_subs off only imitates ctor 'this' behaviour

- status: open
- tags: RPTns_80220994,fn_80221664,ctor,common-subs,induction,register,decomp-hard
- scope: Pack/RPSports/RPTnsScene/RPTns_80220994
- source: orchestrator-1028

symptom: 88.1% best (24b173088 on claude/tns2216h-1028, NOT merged): loop in static inline TnsInitPlayers puts i in r31 as retail, but self is r26 (retail r30), strides r29/28/27 (retail r28/27/26), new sub-object in r5 with address in r4 (retail o in r4, address r3: add r3,self,iv; stw r4,0x138(r3))
cause: Function returns this, calls base ctor then stores vtable: a ctor. In a real ctor MWCC leaves this+iv adds un-CSE'd and makes offset induction variables (li 12/36/72, add this,iv per store) with no pragma; free functions and ordinary members hoist pointer induction variables (addi rX,self,12), hence opt_common_subs off. Even ctor test forms colour this last (r26) and keep o in r5. A ctor form needs invented __ct__ symbols in symbols.txt for fn_80221664 and every sub-object ctor.
fix: Kept nothing (invented static inline helper is a marker, +0.25 not worth it). Dead ends (12): member arrays in a free fn (84.5), self+(i*k+disp) forms (68-75), regular member fn, nested per-player inline, self as local copy +/- opt_propagation off (85.0), pragma sweep (opt_propagation/loop_invariants/lifetimes/dead_assignments/optimization_level 2/3, CSE on/off), CSE-on store helper with separate base/index (86.6, adds CSE temps r24/r25), per-store byte-pointer cast types. With CSE on self is coloured first (best layout: self r31, i r30, pl r29, strides r28-26 = retail with i/self swapped, but 86.6); opt_lifetimes off returns self to last. Next idea: model the real ctor with __ct__ symbols in symbols.txt (needs owner OK) and find what colours this first.
