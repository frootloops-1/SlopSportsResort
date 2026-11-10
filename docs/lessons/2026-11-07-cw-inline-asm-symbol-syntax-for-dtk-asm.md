# CW inline asm symbol syntax for dtk asm

- status: works
- tags: RPBox,asm,R17
- scope: Pack/RPSports/RPBoxScene/RPBox_802cf93c

symptom: dtk lbl@sda21(r0) and mangled callees don't assemble
cause: dtk lbl@sda21(r0) and mangled callees don't assemble
fix: bare symbol for sda21 loads, la rX,sym for li sym@sda21; extern "C" decls under mangled names incl _savegpr_N/_restgpr_N
