# fn_801F9E48: pair read from table avoids lwzux with u32 [idx*2] + struct .i split

- status: works
- tags: lwzux,table,indexed-load
- scope: RPSports_801f9150

symptom: tbl+off loads emitted lwzux (update form) vs target add + lwzx + lwz 4(r6)
cause: same-base add+lwzx peephole merges into lwzux when both words read via (u8*)tbl+off
fix: group = ((const u32*)tbl)[idx*2]; id = ((const MsgPair*)tbl)[idx].i -> 100%
