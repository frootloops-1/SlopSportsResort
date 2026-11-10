# Callee-saved local below self: make it a static inline parameter

- status: works
- tags: regalloc,inline,param,callee-saved
- scope: RPGol_802c16a4
- source: claude/rpgolscene-unsplit

symptom: orig puts a loaded count in a lower callee-saved reg than self
cause: vreg creation order
fix: pass the value (shot->f114) as a static inline's argument; declare work vectors in the caller and pass by ref (y then x)
