# RPGolUtlMtx: last two functions were their own TU (second padded 0.0f, sinit mid-.text)

- status: works
- tags: split,new-unit,sdata2,ctors,RPGolUtlMtx,flip
- scope: Pack/RPSports/RPGolScene
- source: wave3 2026-11-01

symptom: .sdata2 80%, flip FLIP-FAIL (link); fn_802955D0 exact
cause: a second padded 0.0f at 0x804C3FB8 beside the unit's own 0.0f at 0x804C3FA8 and the .ctors sinit sitting mid-.text: fn_80295CB0 + fn_80295D28 are a separate TU; sinit writes only RPGolUtlMtx's own .bss so .ctors/.bss stay
fix: splits.txt: RPGolUtlMtx ends .text 0x80295CB0 / .sdata2 0x804C3FB8; new Pack/RPSports/RPGolScene/RPGol_80295cb0.cpp (.text 0x80295CB0-0x80295D74, .sdata2 0x804C3FB8-0x804C3FC0) with a plain 0.0f; symbols lbl_804C3FB8 -> @141 size 4 scope:local; both Matching, DOL 0. Note flip_gate.py refuses a dirty configure.py so run its steps by hand when the commit adds a new Object line (or commit first, then run it)
