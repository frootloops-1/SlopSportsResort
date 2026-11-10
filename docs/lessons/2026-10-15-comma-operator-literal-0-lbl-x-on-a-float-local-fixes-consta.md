# Comma-operator literal (0, lbl_X) on a float local fixes constant load order

- status: works
- tags: permuter,float,sdata2
- scope: Pack/RPSports

symptom: fn_801F2B30 99.24%: float constant loads in wrong order
cause: MWCC schedules a plain float-literal local differently from (0, x)
fix: f32 scale = (0, lbl_804C2060); found by permuter in under 5 min
