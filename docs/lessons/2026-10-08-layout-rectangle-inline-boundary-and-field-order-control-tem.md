# Layout rectangle inline boundary and field order control temporary storage and paired-single allocation

- status: works
- tags: mwcc,inline,layout,paired-single
- scope: Pack/RPKernel/RPSysLytBounding
- source: 7aecf4ab; docs/tasks/RPSysLytBounding.md

symptom: RPSysLytBounding hit-test has misplaced GetPaneRect temporary and paired-single register differences
cause: MWCC temporary storage follows inline scopes; field evaluation order affects floating-point scratch lifetimes
fix: Source-local rectangle helper; declare projected output vector before displacement input; scale rectangle left/top/right/bottom. Verified code96.704544 to99.32576; constants100. Declaration-only scale reorder and explicit y-first scalar locals do not help.
