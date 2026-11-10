# Same-TU callee auto-inlined into caller: dont_inline blocks its own inline helpers, hand-expand helper

- status: works
- tags: inline,dont_inline,while-loop
- scope: RPTns_802318a4
- source: claude/rptns-2

symptom: caller shows callee inlined (fn_80232BDC loop into fn_80231C54; tiny thunk fn_80232A20 into fn_802331B4) but original has bl
cause: -inline deferred inlines small fns defined earlier; #pragma dont_inline on also stops the fn's own static-inline helper from inlining (score 23-72%)
fix: tiny thunk: wrap in #pragma dont_inline on/reset. Looped fn with helper: keep dont_inline and expand helper by hand as comma-expression ternary in while((e = (n=(q=self->pool)->nxt)==0 ? 0 : (q->cur=n,q->nxt=n->next,n->data->obj)) != 0); declare locals q,n,e
