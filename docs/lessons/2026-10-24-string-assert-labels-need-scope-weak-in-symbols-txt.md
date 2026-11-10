# @STRING@ assert labels need scope:weak in symbols.txt

- status: works
- tags: data-ref,symbols,weak,assert
- scope: egg
- source: claude

symptom: renamed lbl_ to @STRING@...@0 scope:local still scored 99.8
cause: dtk emits it global with an _<addr> suffix because other units reference the string
fix: set scope:weak (precedent setCapTexture); then units that extern the old lbl_ name regress until their hand system_halt(lbl_..) is replaced by the real inline (EGG::LightManager::GetLightObj) (eggLightManager 13/20 -> 17/20)
