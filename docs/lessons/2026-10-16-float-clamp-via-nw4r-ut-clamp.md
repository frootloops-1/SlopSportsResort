# float clamp via nw4r::ut::Clamp

- status: open
- tags: clamp,float,rpbsb
- source: RPBsb_80283fe0 2026-10-16

symptom: orig clamps t in place; Clamp emits separate result reg + extra b (fn_80284080 95.9)
cause: unknown inline shape
fix: Clamp 85-96%; hand if/else worse overall (79.5)
