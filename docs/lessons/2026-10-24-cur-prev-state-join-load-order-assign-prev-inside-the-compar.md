# cur/prev state-join load order: assign prev inside the compare or use cur/prev locals

- status: works
- tags: regalloc,schedule,load-order,box,state-machine
- scope: RPBox
- source: claude

symptom: At the join after if(req!=none){...} original loads cur then prev then cmpw; ours loads prev first (2 differing lines, ~10 fns)
cause: scheduler hoists the load whose value is used first in the following branch
fix: RPBox_802eb834 inline: 'T c=st->cur; T prev=st->prev; if(c!=prev){st->last=prev;..'; RPBox_802f438c/803024c0: 'int previous; if (self->unk2CC != (previous = self->unk2D4)) { self->unk2D8 = previous;' (read fields directly, not via GetState inlines); RPSports_801f1d4c: 's32 prev=self->prev; s32 cur=self->cur; if(cur!=prev)'. Try all per site; two inline instances in one fn may need different forms (fn_802FF6D8 still 3 insns off)
