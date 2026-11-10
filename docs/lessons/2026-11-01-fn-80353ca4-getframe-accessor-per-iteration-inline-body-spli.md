# fn_80353CA4: getFrame accessor, per-iteration inline body, split f32 declarations

- status: works
- tags: accessor,loop-helper,fpr-decl-order,fn_80353CA4,R17,RPBow
- scope: Pack/RPSports/RPBowScene/RPBow_80353C8C
- source: batch 2026-11-01

symptom: 99.9%: frame/loop-counter r31/r28 swap, first-loop temps, fmadds operand order
cause: negated accessor result is an IRO temp coloured before induction temps; per-iteration inline body keeps pAnm a temp; declaration order sets FPR colours while late assignment keeps GPR temps
fix: int getFrame() const {return -mField34;} (R17 57); loop in caller + static inline PlayMoveAnimation(self,i) (R17 58); f32 scale, f2, tx; declared up front, assigned f2, tx, scale. Unit .rodata 99.32 = 4-byte trailing pad, link is 0 bytes. Dead: named f32 scale = lbl[tv] before assignments (32 lines)
