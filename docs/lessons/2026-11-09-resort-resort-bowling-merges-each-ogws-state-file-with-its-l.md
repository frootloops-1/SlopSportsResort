# resort: Resort Bowling merges each ogws state file with its layout UI; ogws UI files are gone

- status: works
- tags: resort,bowling,sport-map
- scope: resort
- source: bowling-rest

symptom: 11 ogws Bowling UI files (bwgText/bwgCount/score/pin brlyt) and the pin/obstacle training modes not found
cause: their strings are absent from the Resort DOL; RPBow_8032ADD8/8032F514 run [ogws twin code, layout UI class, weak tail]
fix: don't search for them; Bowling ends at 0x804FB3B8 (next is Basketball), 0x80489030-0x804C17A8 is Canoeing (WS2_can_)
