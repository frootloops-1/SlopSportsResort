# DebuggerDriver DBInitInterrupts: direct store fixes call, residue is r5 vs r3 + li hoist

- status: open
- tags: NdevExi2AD,DebuggerDriver,regalloc,schedule,sdk-objects
- scope: revolution/NdevExi2AD/DebuggerDriver.c
- source: Wii SDK folder: wii_development_package/NDEV/lib/NdevExi2A.a

symptom: DBInitInterrupts 75.2%: __DBSetDbgCallback bl in ours; target stores __DBMtrHandler inline
cause: Original NdevExi2A.a DebuggerDriver.o (byte-identical to the DOL) has no setter: __DBDbgCallback = __DBMtrHandler is a plain store. Remaining diff: target keeps handler in r3 and sinks li r3,0x19 after addi r4; ours uses r5 and hoists li r3.
fix: Plain assignment gets 86.7. Static handlers, inline setter (void and returning old), local var, void cast, 6 min permuter (no candidate beat base): no gain. Not matched.
