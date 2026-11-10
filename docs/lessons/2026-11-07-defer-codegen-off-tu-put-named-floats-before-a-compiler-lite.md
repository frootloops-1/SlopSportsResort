# defer_codegen-off TU: put named floats before a compiler literal in .sdata2

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBoxScene/RPBox_802de63c

symptom: defer_codegen-off TU: put named floats before a compiler literal in .sdata2
cause: defer_codegen-off TU: put named floats before a compiler literal in .sdata2
fix: define them before that function inside namespace X { extern "C" const f32 lbl = v; } so values don't propagate
