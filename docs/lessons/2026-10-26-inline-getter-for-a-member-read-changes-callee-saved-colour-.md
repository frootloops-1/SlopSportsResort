# inline getter for a member read changes callee-saved colour: fn_801E8ED0 closed

- status: works
- tags: forecast,regalloc,inline-getter,inline-expansion,RPSports_801E7EB4,fn_801E8ED0
- scope: fn_801E8ED0
- source: forecast-regalloc

symptom: fn_801E8ED0 99.9%: msg = lbl_804BF710->msg held in r27/r25 instead of r28 across two findTextBox/setMessage calls; 7 decl positions only moved it between r27 (decl before nested j-loop) and r25 (after)
cause: the target read the field through an inline accessor, so the value is an inline-expansion @-variable (forecast model: @ vars coloured before named locals), not a named local fed by a plain load
fix: Main::getMessage() const { return msg; } (name inferred) and msg = lbl_804BF710->getMessage(); -> 100%. Also matched: static inline helper taking msg as a parameter, or a helper holding msg as its own local. Failed: declare-up-front at 7 positions, shared i/j counters declared up front (46 lines worse), a per-textbox helper PsSetText(layout,name,msg,id)
