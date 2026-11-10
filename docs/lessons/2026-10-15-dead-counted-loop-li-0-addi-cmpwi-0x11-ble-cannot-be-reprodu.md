# Dead counted loop li 0/addi/cmpwi 0x11/ble cannot be reproduced

- status: fails
- tags: loop,dead-code
- scope: RPTns
- source: RPTns_80220994

symptom: orig has empty 18-iteration loop in fn_802210D0
cause: MWCC deletes empty/dead loops; inline asm disables subic. record forms
fix: open: for/while/do/goto, dummy array stores, empty ctor arrays, opt 3 all removed
