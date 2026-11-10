# bool member vs u8 for == comparisons

- status: works
- tags: types,bool
- scope: Pack/RPSports/RPSportsCommon/RPSysNunchukCheckScene/fn_801E3760

symptom: extra extrwi (u8 mask) before comparing isFreestyle() with a member flag
cause: member declared u8; orig compares bool to bool (int promotion, no mask)
fix: declare the 0x60 flag as bool
