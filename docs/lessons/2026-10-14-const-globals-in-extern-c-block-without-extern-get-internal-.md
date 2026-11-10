# Const globals in extern C block without 'extern' get internal linkage and are dropped

- status: works
- tags: linkage
- scope: RPGol_802b08a0
- source: RPGol_802b08a0

symptom: missing const symbols
cause: C++ const internal linkage
fix: extern const float X = v;
