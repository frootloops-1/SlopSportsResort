# sdata unreferenced 4-byte zero before a 7-char literal: 8-byte literal is 8-aligned

- status: works
- tags: sdata,string-literal,alignment,NWC24
- scope: revolution/NWC24/NWC24MsgCommit
- source: NWC24MsgCommit sdata session 2026-10-26

symptom: orig .sdata has an unreferenced zero word between a var and the first literal; mine packs the literal 4 bytes earlier
cause: MWCC gives an 8-byte string literal 8-byte alignment; original literal was "DATA\r\n\0" (size 8), the zero word is alignment pad
fix: write the literal with an explicit \0 to make it 8 bytes; cross-check Petari (SMG) symbols.txt, which marks such literals align:8
