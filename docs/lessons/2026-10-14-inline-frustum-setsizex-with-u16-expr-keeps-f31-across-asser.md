# Inline Frustum::SetSizeX with u16 expr keeps f31 across assert: pass (f32)u16 local

- status: works
- tags: float,u16,inline,assert
- scope: RPTns_802318a4
- source: claude/rptns-2

symptom: SetSizeX(u16 expr) kept converted float in f31 across the system_halt (psq_st f31 prologue); orig recomputes the conversion after the assert
cause: implicit int->f32 of an expression arg is CSEd into a callee-saved fpr
fix: u16 w = Screen::GetSizeXMax(); scr->SetSizeX((f32)w); wide: u16 hw=(u16)(0.5f*GetSizeXMax()); SetSizeX((f32)hw) twice
