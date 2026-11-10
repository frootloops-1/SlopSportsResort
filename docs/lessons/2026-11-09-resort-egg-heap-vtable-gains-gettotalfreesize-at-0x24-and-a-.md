# resort: EGG::Heap vtable gains getTotalFreeSize at 0x24 and a name at 0x34; ConfigurationData has an extra virtual at 0x2C

- status: works
- tags: resort,EGG,Heap,vtable
- scope: resort
- source: RP batch 5 (2026-11-09)

symptom: heap calls through the vtable hit the wrong slot
cause: newer EGG
fix: eggHeap.h/eggExpHeap.h/eggFrmHeap.h/eggSystem.h carry the Resort slots
