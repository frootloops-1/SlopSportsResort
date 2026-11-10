# Vtable symbol 4 bytes too big with trailing 0 = alignment pad before next TU, not a slot

- status: works
- tags: vtable,symbols,padding
- source: sp8020f-1104

symptom: __vt__18RPSportsMailHolder 0x18 retail vs 0x14 ours; 14 vtables end GenMessage,0
cause: dtk sized the symbol up to the next TU's 8-aligned .data start
fix: symbols.txt size 0x14; no header change (IRPSysHostIOSocket untouched)
