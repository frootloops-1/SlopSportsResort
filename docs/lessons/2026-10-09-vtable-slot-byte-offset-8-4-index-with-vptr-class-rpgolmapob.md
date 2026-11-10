# Vtable slot byte offset = 8 + 4*index with vptr class (RPGolMapObjBase)

- status: works
- tags: golf,vtable,slot,RPGolMapObjBase
- scope: RPGolMapObjBase
- source: sonnet

symptom: need slot 0x20/0x5c/0x64
cause: CW 8-byte RTTI header
fix: filler virtuals so index = (off-8)/4: 0x1c=5,0x20=6,0x5c=21,0x64=23
