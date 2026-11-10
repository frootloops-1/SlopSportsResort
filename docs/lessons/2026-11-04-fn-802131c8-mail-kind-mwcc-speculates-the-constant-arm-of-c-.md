# fn_802131C8 mail kind: MWCC speculates the constant arm of c ? 2 : kind (li before branch, mr r8,r9); retail keeps kind in r8

- status: open
- tags: ternary,select,colour,rpsports,80211b60
- source: sp8020f-1104

symptom: one extra mr r8,r9 at the fn_801CEBF0 call; arg loads must stay before the branch
cause: ternary lowers to li t,2; bf; mr t,kind; !c/==0/<=0/casts canonicalise to the same; if-statement or comma/assign or inline-call arg moves the arg loads after the branch; an inline whole-call helper sinks addi/clrlwi args; the dont_inline region must stay (fn_80212160 auto-inlines otherwise)
fix: open: need an arg-position form lowering to t=kind; if(c) t=2
