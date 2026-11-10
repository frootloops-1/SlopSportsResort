# Shared named GPR (string/addr base) coloured before named locals: turn name/suffix into call-arg temps

- status: works
- tags: regalloc,temps,callee-saved,RPSports
- scope: RPSports_801fba3c
- source: fn_801FBEE4

symptom: fn_801FBEE4: pool string base got r29, player r27, suffix r28 (target base r27, player r29, suffix r28)
cause: the shared string-pool base is an expression temp (high vreg, coloured first); named locals name/suffix were coloured after it
fix: drop the named locals: setMessage(msg,id,0,2,fn_801F8534(player),fn_801F84C0(player)); the call-arg temps (created later than the base) are coloured first, base lands in r27. Also one function-level 'int i' for all three for-loops moved the last loop index r26->r27
