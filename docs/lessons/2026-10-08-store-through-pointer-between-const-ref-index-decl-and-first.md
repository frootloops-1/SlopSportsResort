# Store through pointer between const-ref index decl and first use stops first-access fold

- status: works
- tags: mulli,constant-index

symptom: first pages[0] access folds to stb 0(r4) instead of li+mulli
cause: constant propagated into first use of const s32& to local
fix: put 'self->channel = ch' (ch computed into a local) after 'const s32& type = typeVal;' (fn_801E2970 89.8->95.5)
