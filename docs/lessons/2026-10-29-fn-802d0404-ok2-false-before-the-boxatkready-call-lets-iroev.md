# fn_802D0404: ok2 = FALSE before the BoxAtkReady call lets IroEval merge the ready/ok1 branch chain

- status: fails
- tags: fn_802D0404,RPBox_802cf93c,branch-threading,bool
- scope: RPBox_802cf93c

symptom: target zero-inits hitOK, ok2, ready (r30,r27,r28) before the v40(2) call and keeps ok1 separate; ours sinks ok2=0 after the call into r0 (98.8)
cause: with ok2=FALSE moved before the call the join block starts with the ok1 test, so fn_00455350/starts_with_branch_cond merges ready into the valid test (ok1 vanishes)
fix: failed: ok2 declared before ok1 = BoxAtkReady (98.4), open-coded ok1 = FALSE; if (v40 && w3E0==0) ok1 = TRUE (98.4). Needs a non-branch first statement in the join block that emits no code after the call
