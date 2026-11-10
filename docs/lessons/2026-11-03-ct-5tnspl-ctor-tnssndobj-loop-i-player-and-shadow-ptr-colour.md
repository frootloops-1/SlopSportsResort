# __ct__5TnsPl ctor: TnsSndObj loop i/player and shadow-ptr colour order (parked 99.8)

- status: fails
- tags: RPTnsScene,regalloc,ctor,inline,colour_sim
- source: claude/tns5530-1103

symptom: __ct__5TnsPlFi 99.8: TnsSnd3D loop counter i r25 vs r26, player r26 vs r25, new TnsShadow ptr r25 vs r27
cause: colour_sim: all in sweep 1, descending vreg; target needs vreg(shadow) > vreg(i) > vreg(player) (i.e. shadow's @ earliest), ours has player @10560 < i @10575 < shadow @10592 (source order). Needs player/i to be late (optimizer) temps or the TnsSndObj expansion numbered after the shadow new
fix: dead ends: named player local in TnsPl ctor (97.5, load moves before new), local copy p=&player in TnsSnd3D (99.6), TnsSndObj() : TnsSnd3D(global expr) (99.6), player read inside loop (97.3, no LICM across calls), static inline new-helpers for TnsSndObj/TnsShadow (flat/98.0). mwcc_dbg fn name for this ctor is '__ct' (TnsPl crashes)
