# Single .sdata2 string ptr loaded in a 1-iteration loop = local 1-element array

- status: works
- tags: sdata2,strings,array-init,scheduling
- scope: RPTns_80246eec
- source: opus worker 2026-10-14

symptom: static const char* const ptr: lwz scheduled one slot early in do/while(--i>=0) loop of 1
cause: source used local const char* a[1] = {"str"} (scalarised array init, compiler-named @NNN in .sdata2)
fix: write the local array; rename symbols.txt entries to the compiler's @NNN scope:local names (RPTns_80246eec fn_8024720C 97.9 -> 99.8)
