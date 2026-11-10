# extern const on a writable-section global changes codegen: check whether the declaration is used and whether the symbol is .sdata/.data

- status: works
- tags: const,sdata,extern,scheduling,hoist
- scope: RPSportsCommon

symptom: fn_80201240 94.6 with two lfs hoisted above the prologue stw; fn_8020DED4 50.2
cause: lbl_ symbols placed in .sdata/.data by symbols.txt are non-const globals in the original; declaring them extern const let the compiler hoist/CSE the loads
fix: Declare writable-section scalars non-const (extern f32 x). Scan 2026-10-31: 19 NonMatching RPSportsCommon units only declare lbl_804BDD30/34 and never use them (object identical); across 21 NonMatching files 52 per-symbol trials gave 1 gain (lbl_804BDDA0 in RPSports_8020b294, fn_8020DED4 50.2->54.7), 45 no effect, 7 REGRESSIONS (RPBsb_80275a44, RPBsb_80285870, RPBsb_8025ff94): those const declarations are real, so test per symbol and keep only measured gains.
