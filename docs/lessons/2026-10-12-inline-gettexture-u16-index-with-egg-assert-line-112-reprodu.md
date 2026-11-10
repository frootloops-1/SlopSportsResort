# Inline getTexture(u16 index) with EGG_ASSERT_LINE(112,...) reproduces both assert strings; weak @STRING@ labels need symbols.txt names

- status: works
- tags: assert,string,@STRING@,symbols.txt,LightTextureManager,weak
- scope: RPGrpDrawPathLightMap
- source: sonnet worker + coordinator 2026-10-12

symptom: Assert string relocs score as lbl_ vs @STRING@ and data 84%
cause: objdiff pairs by name; ours are weak @STRING@<fn>[@0]
fix: Rename lbl_ string labels to @STRING@<mangled fn>@0 / @STRING@<mangled fn> with scope:weak data:string (precedent setCapTexture); param name must be index for the string
