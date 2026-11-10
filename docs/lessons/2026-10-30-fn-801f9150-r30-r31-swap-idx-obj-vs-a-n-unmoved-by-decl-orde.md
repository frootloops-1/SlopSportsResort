# fn_801F9150: r30/r31 swap (idx+obj vs a/n) unmoved by decl order, row helpers, field copy; regsearch generic 10min no result

- status: fails
- tags: regalloc,coloring
- scope: RPSports_801f9150

symptom: idx/obj node colored r30, a/n r31, target opposite; copy temps order also differs
cause: unknown; mwcc_dbg shows a colored first despite higher degree on obj
fix: none: tried field-by-field copy (86.9), static-inline getters (same), swapped declaration order (same), regsearch --generic (best reg=9 residue)
