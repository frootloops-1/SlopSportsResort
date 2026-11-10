# Asm body needs member-function-pointer constants the C no longer emits

- status: works
- tags: ptmf,data,asm,R17
- scope: RPBsbScene
- source: RPBsb_8026eccc/802803b0/80283fe0

symptom: link: undefined lbl_<addr> after converting a fn that used member-pointer constants (@NNN 12-byte {0,off,-1/0x28} objects in .data)
cause: the constants were only created by the C body, now under #if 0
fix: hand-define every such @NNN object as static u32 lbl_<addr>[3] = {...} in retail order, wrapped in #pragma push/force_active on/pop
