# Call a 5-arg fn with 2 args via function-pointer cast

- status: works
- tags: call,args,arity
- scope: RPTns
- source: RPTns_80220994

symptom: callee takes r3-r7 but some callers set only r3/r4
cause: original prototype mismatch / forwarding
fix: ((void(*)(A,B))fn)(a,b) at that call site (fn_80220F88)
