# static Vec with dtor: split link record symbol

- status: works
- tags: bss,symbols,register_global_object,rpbsb
- source: RPBsb_8027d3ec 2026-10-16

symptom: static init reloc ...bss.0 vs lbl_ (99.8)
cause: symbols.txt sized vec+next link record as one 0x18 object
fix: split into 0xC vec + 0xC link record symbol (fn_8027E038 -> 100)
