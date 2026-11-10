# const dynamic-init global array fixes sinit load scheduling

- status: works
- tags: sinit,scheduling,const,bss
- scope: RPUtlAccAnalyzer
- source: claude-opus

symptom: __sinit byte copies of DrawGX colors: orig hoists one lbz (GREEN+2/r11) and addi before lfs; ours loads in order (94.9%)
cause: original array was const (const objects with non-constant initializers still go to .bss via sinit but schedule differently)
fix: extern const GXColor arr[4] = {RED, GREEN, BLUE, ORANGE}; (extern keeps it emitted) -> sinit 100% (RPUtlAccAnalyzer)
