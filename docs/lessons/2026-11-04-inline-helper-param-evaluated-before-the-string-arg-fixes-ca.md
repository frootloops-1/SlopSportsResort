# Inline helper param evaluated before the string arg fixes call/string order and callee-saved colouring (fn_8021013C SpSeRemote)

- status: works
- tags: inline-param,colour,order,rpsports,8020f530
- source: sp8020f-1104

symptom: string address computed before fn_801D0120 call and remote/id in r31/r30 instead of r30/r31
cause: retail evaluates the remote (call) before the name; args are evaluated right-to-left
fix: SpSeRemote(name, fn_801D0120(...)) with remote as the LAST param; body loads mgr, then changeNameToIdRP(name)
