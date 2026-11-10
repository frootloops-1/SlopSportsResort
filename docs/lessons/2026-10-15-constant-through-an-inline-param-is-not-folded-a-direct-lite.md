# Constant through an inline param is not folded; a direct literal is

- status: works
- tags: float,constant-folding,inline,sdata2,link-flip,extern-pool-label
- scope: Pack/RPSports/RPGolScene/RPGol_802af8e8
- source: claude/nm-link-1 2026-10-15

symptom: Replacing extern pool labels (needed to flip: orig-only lbl_ symbols are undefined at link) with literals made x - 0.0f fold away; fn 100 -> 93.5, .text -8 B.
cause: MWCC folds x - 0.0f for a literal at the use site but not when 0.0f arrives through an inline function parameter; orig code was the inline helper called with constants.
fix: Call the existing inline helper with the constants (golRemap(0.0f, A, 0.2f, 1.0f, d)); 1.0f-0.2f still folds to the 0.8f pool entry. RPGol_802af8e8 fn_802AFB80 back to 100, DOL 0 bytes.
