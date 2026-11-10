# Constant re-materialised for a store = inlined helper with folded condition

- status: works
- tags: inline,constant,li
- scope: RPTns_80246eec
- source: opus worker 2026-10-14

symptom: target emits fresh li r0,0; stw where ours reuses a zero register; ours 4 bytes larger
cause: store comes from an inlined helper (if(state!=mode){..} state=mode) whose compare folded after state=-1
fix: call the same inline helper the sibling function uses (fn_80247170 -> 100)
