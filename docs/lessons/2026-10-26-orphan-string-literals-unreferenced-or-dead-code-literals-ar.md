# Orphan string literals: unreferenced or dead-code literals are never emitted in C (-ipa file)

- status: fails
- tags: sdata,string-literal,dead-code
- scope: revolution/NWC24/NWC24MsgCommit
- source: NWC24MsgCommit sdata session 2026-10-26

symptom: trying to emit an unreferenced literal to fill an sdata gap
cause: MWCC drops literals whose only uses are folded/dead (if(0), dead store, empty inline fn, 0-trip loop, constant switch); a non-static dead fn keeps it in the .o but the linker strips both
fix: none; look for alignment (8-byte objects) or an explicit-NUL literal instead
