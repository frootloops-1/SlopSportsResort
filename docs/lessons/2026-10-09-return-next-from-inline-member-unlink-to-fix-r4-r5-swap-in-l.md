# Return next from inline member Unlink() to fix r4/r5 swap in list-removal loop

- status: works
- tags: regalloc,inline,linked-list,RPUtlObject
- scope: RPUtlObject.cpp

symptom: manual loop with prev/next locals gave next=r5, reload=r4 (orig next=r4, reload=r5), 98.57%; outer/inner decl, for-loop, order swaps, after var all failed or worse (96.2%)
cause: orig inlines an Unlink() that returns the old next; loop is node = node->Unlink()
fix: member inline Node* Unlink(){prev=previous; following=next; if(prev)prev->next=following; if(next)next->previous=previous; next=0;previous=0;state=0; return following;} (fn_801BFC5C -> 100%)
