# size:0x8 .sdata float at unit end is alignment padding: set size 0x4, use scalar

- status: works
- tags: symbols,sdata,padding,static
- scope: RPBsb
- source: claude/mr-b-1101

symptom: [2] arrays whose second element only pads the end of a unit's 8-aligned .sdata
cause: dtk then emits a gap_ symbol for the trailing 4 bytes; scalars keep .sdata 100 and DOL 0
fix: symbols.txt lbl_804BE238/804BDF08/804BE3A8 -> 0x4 (commit ed2c5b4a7); RPBsb_80273950 lbl_804BE378 and RPBsb_80263eec lbl_804BE1B8 also became function-local statics
