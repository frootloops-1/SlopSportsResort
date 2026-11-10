# -inline deferred: initialized globals/local statics are parse-time (all before jump tables); only real class vtables land after jump tables

- status: works
- tags: data,vtable,jumptable,inline-deferred,order
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c
- source: claude/d1f1d4c-b-1031

symptom: .data target: string tables, then @N jump table, then {0,0,fn..} vtables, then weak @STRING@ assert strings; hand void*[] vtables cannot be placed after the jump table
cause: MWCC emits every initialized global, file static and function-local static (even inside an inline fn) at parse time in source order; jump tables at compile time; compiler-generated __vt__ (RTTI off: {0,0,slots}, pure virtual=0) after all functions; weak inline-fn @STRING@ objects last (scratch test)
fix: Tables: define in TU in target order (strings pool in initializer order). Vtables need real classes with virtual members (slot fns become mangled members -> symbols.txt renames); RPSports_801f1d4c still blocked on this (12 vtables, ~46 slot fns)
