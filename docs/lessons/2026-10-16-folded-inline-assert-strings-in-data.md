# folded inline assert strings in .data

- status: works
- tags: assert,data,egg,rpbsb
- source: RPBsb_80283fe0 2026-10-16

symptom: .data has assert strings of inlines the header lacks
cause: original header inlines had EGG_ASSERT
fix: local helper classes with EGG_ASSERT under #line N "eggFrustum.h"; define order controls .data order
