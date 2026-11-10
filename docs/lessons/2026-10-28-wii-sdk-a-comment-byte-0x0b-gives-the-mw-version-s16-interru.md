# Wii SDK .a .comment byte 0x0B gives the mw_version; s16 interrupt type param

- status: works
- tags: mw_version,comment,sdk-objects,NdevExi2AD,OSInterrupt
- scope: revolution/NdevExi2AD,revolution/OS/OSInterrupt
- source: Wii SDK folder NdevExi2A.a

symptom: DBInitInterrupts stuck at 86.7: handler in r5 and li r3,0x19 hoisted above the store
cause: Unit needs GC/3.0a3 (SDK .o .comment byte 0x0B = 0x0E; 3.0a5+ writes 0x0F) and __OSSetInterruptHandler's first param is s16 (SDK __OSInterrupt), not an enum
fix: mw_version GC/3.0a3 on DebuggerDriver.c plus s16 prototype/definition: 100%, DOL 0 diff, Matching. Check this version byte in original .a objects before hunting source shapes.
