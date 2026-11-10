# Walk list through base pointer and hoist colour local to function scope (b340 D0EC/D40C)

- status: works
- tags: stack-slot,colour,pointer-base,b340
- scope: RPSportsCommon/RPSports_8020b340
- source: claude/b340-1104a

symptom: extra add/addi and wrong 0x1734 offset; colour struct at wrong stack slot
cause: Indexing self directly vs via a List* base changes address formation; block-scoped _GXColor gets a different slot
fix: List* lst = (List*)((u8*)self + 0x1730); lst->it[i]; declare col at function scope; by-value scaleAlpha. D0EC 98.1->99.8, D40C 99.7->99.8
