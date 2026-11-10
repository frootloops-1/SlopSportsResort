# Raw-load float locals merge into load temps (b340 C878)

- status: works
- tags: register,float,merge,callee-saved
- scope: RPSportsCommon/RPSports_8020b340
- source: claude/b340-1104c 6db825780

symptom: hoisted 0.5f in wrong callee-saved FPR
cause: f32 ax = a->x (raw load) merges into the load temp; ax = a->x + dx stays a named var
fix: Hold raw loads in locals, apply offsets at use. C878 81.2->82.3; all-inline gives retail callee-saved order but moves loads after stores
