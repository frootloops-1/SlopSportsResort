# Sdata tex0 table with size 0x20 align 32: use 8-byte static array with aligned(32)

- status: works
- tags: nw4r,ef,sdata,align
- scope: nw4r/ef

symptom: ef_drawbillboardstrategy DOL check failed; .sdata 40% (orig sym size 0x20 align 32), 32-byte array moves to .data and regresses InitGraphics
cause: symbol size 0x20 is alignment padding; real array is 8 bytes in .sdata
fix: static u8 x[8] __attribute__((aligned(32))) = {...}
