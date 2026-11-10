# mwcc vreg order: named locals, then temps by descending creation id; new temps late

- status: works
- tags: register,vreg,numbering,new,permuter
- scope: RPSportsCommon/RPSports_801f1d4c
- source: claude/sp801f1-1104d f550d6a66

symptom: SpMdlSetD mgr/anm r24 vs r25, unreachable by locals, helpers, blocks, register, ternaries; permuter 20 min only ties
cause: Params, named locals (reverse decl, blocks ignored), then temps by descending @id; inline/?: temps early, new-result temps later, optimizer temps last. Value needs a temp created after a later new-expression
fix: open: parked; look for a source order where mgr/anm are produced after the loop-1 screen new
