# WPAD/KPAD batch: rxBufs[idx] stride, u32 loop unroll, literal ternary, struct-size index

- status: works
- tags: WPAD,KPAD,loop,unroll,ternary,array-stride,join-moved
- scope: revolution/WPAD/WPADHIDParser, revolution/KPAD/KPAD
- source: claude/nm-4 2026-10-16 sonnet batch 2

symptom: __a1_37_data_type 87.7, __a1_22_ack 93.4, KPADRead 96.8
cause: rxBufs+idx*N on u8[2][N] scales twice; int loop counter blocks unroll; extra early return; &inside_kpads[chan] uses sizeof 0x538 not 0x524
fix: __a1_37 ->100: p_cb->rxBufs[p_cb->rxBufIndex], u32 i for the clear loop (int gives pointer-bump loop), drop _devCmpt block; __a1_22 ->99.7: status=(err==0)?0:-3 literal; KPADRead ->99.4: no WPADGetStatus early return, (u8*)inside_kpads+chan*0x524, ring wrap 16
