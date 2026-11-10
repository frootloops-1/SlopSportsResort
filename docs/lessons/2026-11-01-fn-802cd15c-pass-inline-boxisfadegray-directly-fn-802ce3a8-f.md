# fn_802CD15C: pass inline BoxIsFadeGray directly; fn_802CE3A8 / fn_802CDFC0 dead ends

- status: works
- tags: inline-helper,fn_802CD15C,fn_802CE3A8,fn_802CDFC0,RPBox
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc
- source: unit sweep 2026-11-01

symptom: fn_802CD15C 99.9: case-4 r4/r5/r6 swap; fn_802CE3A8 99.8: BoxData copy-1 callee-saved rotation; fn_802CDFC0 99.8: FPR colours
cause: local bool + if-block vs existing helper; CE3A8 needs branch-2 n web coloured between copy-2 and copy-1 temps; CDFC0: t first + in-place remaining -= step gives exact FPRs but post-RA scheduler hoists loads (96.3)
fix: fn_802CD15C: BoxFade(fog, 1.0f - r, BoxIsFadeGray(self)). Dead: CE3A8 kind/mode order, inline idx, ternary/if-else n, int m, && / || forms, 8-min regsearch; CDFC0 all 8 statement orders, direct global step
