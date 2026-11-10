# HermiteKey inline FPR coloring: dead ends (fn_802E9974/fn_802E9774)

- status: fails
- tags: mwcc,fpr,hermite,RPBox
- scope: RPBox_802e9774

symptom: FPR numbering of inlined Hermite helper differs (rot f24 vs f26) at 99.1-99.6%
cause: unknown; shared inline source form probably not the original
fix: failed: temp decl order hill-climb, all 108 stmt orders, frame local at call site, 7 expression variants. Wins: enum-typed ternary gives branchless select; 2-iteration for loop stops CSE of &self->member; struct locals first-declared = highest stack addr
