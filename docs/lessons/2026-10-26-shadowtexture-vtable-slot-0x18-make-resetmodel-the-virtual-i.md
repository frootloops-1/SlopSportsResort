# ShadowTexture vtable slot 0x18: make ResetModel the virtual InitList override (.data 92.86 -> 100)

- status: works
- tags: egg,eggShadowTexture,vtable,rename,InitList
- scope: egg/gfxe/eggShadowTexture

symptom: .data 92.86%: __vt__ slot 0x18 pointed at ModelSnapshot::InitList instead of ShadowTexture's own function
cause: symbols.txt named the override ResetModel and the header declared it non-virtual
fix: rename symbol to InitList__Q23EGG13ShadowTextureFv, declare virtual void InitList(), rename definition and the 2 RPTns_8021ba24 references; DOL 0 diff, RPTns_8021ba24 97/101 unchanged
