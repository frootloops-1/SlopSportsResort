# Large local char array off by 4 bytes: try size 255

- status: works
- tags: stack,local,array,va_list,vsprintf,alignment,RPGrpShadowTexture
- scope: RPGrpShadowTexture::Replace
- source: sonnet worker, verified 2026-10-12

symptom: Local char buffer[256] sits at sp+0x78 after a 12-byte va_list at sp+0x68; original has it at sp+0x74, frame size equal
cause: MWCC 8-aligns a 256-byte local char array; a 255-byte one only needs 4-alignment
fix: Declare char buffer[255] (sizeof(buffer) uses stay valid). Declaration order, local struct, unsigned char, inner blocks, char* alias did not change it.
