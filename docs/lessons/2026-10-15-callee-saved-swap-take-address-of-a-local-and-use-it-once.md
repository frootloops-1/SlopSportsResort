# Callee-saved swap: take address of a local and use it once

- status: works
- tags: regalloc,callee-saved
- scope: RPTnsScene
- source: claude/rptns-3

symptom: idx/id or w swapped between r29/r31 (EB40, F13C, BB1C)
cause: register allocation order of locals
fix: u32* pid=&id; f32* pw=&w used once through the pointer
