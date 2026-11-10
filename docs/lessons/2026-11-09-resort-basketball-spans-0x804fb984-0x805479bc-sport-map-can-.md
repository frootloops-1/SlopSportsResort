# resort: Basketball spans 0x804FB984-0x805479BC; sport_map can/bic votes there are false

- status: works
- tags: resort,sport-map,basketball
- scope: resort
- source: basketball

symptom: sport_map tags parts of Basketball as Canoeing/Cycling
cause: can votes come from pool offsets landing mid-string; WS2_bic_passcut is an effect bsk passes to RPSysEffect
fix: 0x804FB3B8-0x804FB984 is Bowling (RPBow_804FB3B8, called from RPBow_8032ADD8); Basketball = 68 units in src/Sports2/Bsk/
