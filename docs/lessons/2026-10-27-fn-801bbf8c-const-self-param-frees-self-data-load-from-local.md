# fn_801BBF8C const self param frees self->data load from local-store deps

- status: works
- tags: scheduling,const-param,alias,RPUtlCollisionModel
- scope: Pack/RPUtility/RPUtlCollisionModel
- source: claude/rputl-cmod-1027

symptom: prologue: lwz r30,0(r3) (self->data) scheduled after stw count/stfs pt stores; 18 lines
cause: loads via non-const pointer params depend on earlier stores to address-taken locals (count, pt)
fix: declare const CollisionModel* self (and on callee fn_801BB9B8): 96.5 -> 100
