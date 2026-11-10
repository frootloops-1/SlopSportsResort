# Copy assignment vs copy-init of EGG::Vector2f

- status: works
- tags: vector,copy,float
- scope: Pack/RPSports/RPSportsCommon/RPSysNunchukCheckScene/fn_801E333C

symptom: orig copies cursor pos with lfs/stfs pairs; copy-init produced lwz/stw
cause: copy-initialisation uses the implicit word copy; assignment uses VEC2 operator= with float moves
fix: EGG::Vector2f pos; pos = getActiveCursorPos();
