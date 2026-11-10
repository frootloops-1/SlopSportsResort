# extern const f32 X = 1.0f in a TU leaves duplicate pooled literals

- status: works
- tags: data-ref,sdata2,pool
- scope: project
- source: claude

symptom: code identical but target uses one shared @N literal and ours has a second
cause: a TU-defined 'extern const f32/f64' constant is propagated into a pooled literal at every use
fix: delete the definition, use plain literals, rename the symbols.txt entries to @N size 4/8 scope:local (RPUtl_801BFEA8, ButtonA fn_801D017C); a literal 0.0f where target loads a shared sdata2 float: init from the extern const symbol instead
