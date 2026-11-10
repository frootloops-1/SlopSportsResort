# Vtable 92.86%: slot 0x18 override named ResetModel vs ModelSnapshot::InitList (name conflict)

- status: open
- tags: vtable,symbols,header
- scope: egg/gfxe/eggShadowTexture
- source: shadow-1026

symptom: __vt__ShadowTexture .data 92.86: reloc at +0x18 targets InitList__ModelSnapshot instead of ResetModel__ShadowTexture
cause: header declares non-virtual ShadowTexture::ResetModel; the retail slot is an override of ModelSnapshot slot 0x18 (InitList)
fix: virtual void InitList() in eggShadowTexture.h + cpp def + symbols.txt rename ResetModel__Q23EGG13ShadowTextureFv -> InitList__...: .data 100, DOL 0 diff; but RPTns_8021ba24.cpp externs ResetModel__Q23EGG13ShadowTextureFv (needs edit). Patch /tmp/scratch-shadow-1026/vtable-initlist.patch
