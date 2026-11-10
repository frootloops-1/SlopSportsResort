# DebuggerDriver DBInitInterrupts: needs GC/3.0a3 + s16 __OSSetInterruptHandler param

- status: works
- tags: NdevExi2AD,DebuggerDriver,compiler-version,prototype,schedule,sdk-objects
- scope: revolution/NdevExi2AD/DebuggerDriver.c
- source: NDEV/lib/NdevExi2A.a DebuggerDriver.o

symptom: store of fn address before a call: handler in r5, li r3,arg hoisted above stw; target r3 with li after stw; no source shape changed it
cause: Pre-RA scheduler: GC/3.0a5.2 always hoists the arg li; GC/3.0a3..3.0a5 only keep it late when the callee param is s16 (SDK __OSInterrupt), not int/enum. SDK .comment header 0x0E = GC/3.0a3.x
fix: mw_version GC/3.0a3 for the object + s16 prototype gives a byte-identical object (text/relocs/symtab/comment). Read the SDK object's .comment version byte (0x0E vs 0x0F) before source-hunting a scheduling residue
