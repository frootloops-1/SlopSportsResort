# RPBox cf93c: literal zero reset matches with two ordered symbolic asm instructions

- status: works
- tags: RPBox_802cf93c,fn_802DD1F0,inline-asm,scheduling,R17
- scope: RPBox_802cf93c
- source: 2026-11-03 codex-rpbox-cf93c-20261103; build/evidence/rpbox-pass

symptom: Exact fn_802DD1F0 referenced undefined lbl_804C4E10; a literal let the first stw precede lwz pE4, blocking source linking.
cause: The mutable extern imposed a scheduler dependency absent from a literal. Full assembly reset lost compiler immediate caching and rematerialized -1/0.
fix: Use literal zero and register self; a two-instruction asm block (.scheduling off; li one,1; lwz e4,0xe4(self)) supplies one to seq74.cur/next+w70 and e4 to v10. Reset stores stay C++. No fmr needed. Function remains exact, all data100, order0; temporary source link succeeds, original size, 492 bytes differ only in ten other functions. Configured NonMatching DOL0. Marked R17; not a full object match.
