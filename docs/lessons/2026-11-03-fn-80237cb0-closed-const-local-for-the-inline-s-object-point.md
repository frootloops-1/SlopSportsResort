# fn_80237CB0 closed: const local for the inline's object pointer

- status: works
- tags: colour order,regalloc,inline,const,RPTns
- scope: Pack/RPSports/RPTnsScene/RPTns_8023758c

symptom: inline TnsPlayId(spInstance,...) param took r29 (coloured before c/a); retail r28 shared with a/r
cause: inline param @ temp is numbered above all named locals so it colours first; a NON-const local assigned only from a global is also turned into a global-copy @ temp, so the earlier 'snd local' tries changed nothing
fix: TnsSndMgr* const snd = spInstance; TnsPlayId(snd,...): const keeps snd a named low vreg, coloured after a, takes the lowest used free callee reg (r28). Colour pick rule: lowest-numbered already-used callee reg free of coloured neighbours, else next new from r31 down
