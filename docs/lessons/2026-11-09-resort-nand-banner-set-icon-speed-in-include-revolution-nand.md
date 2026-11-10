# resort: NAND_BANNER_SET_ICON_SPEED in include/revolution/NAND/nand.h shifts by FRAME, SDK shifts by 2*FRAME

- status: open
- tags: resort,NAND,macro,initBanner
- scope: resort
- source: RP batch 5 (2026-11-09)

symptom: initBanner 98.7%
cause: shared macro differs from the SDK NANDSetIconSpeed
fix: RPSysSaveDataMgr writes the 2*i shift by hand; fix the macro once its other users are checked
