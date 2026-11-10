# 8x-unrolled ctr loop is a plain for loop (RPGolMapObjBase fn_8028FA1C)

- status: works
- tags: golf,loop,unroll,RPGolMapObjBase
- scope: RPGolMapObjBase
- source: opus

symptom: 8x unrolled ctr loop + remainder + 0x7FFFFFFE bound check
cause: MWCC unrolls simple loops itself
fix: for(int i=0;i<n;i++) with n=(u16) virtual return, reload self->f4->entries[i] each pass; u8 param
