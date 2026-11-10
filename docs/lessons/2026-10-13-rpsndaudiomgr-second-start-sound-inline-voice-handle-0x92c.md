# RPSndAudioMgr second start-sound inline (voice handle 0x92C)

- status: works
- tags: rpgol,sound,inline
- source: RPGol_802b90b4

symptom: start-sound pattern with different handle and name check
cause: two inlines: system SE checks 'BGM' at name[7..9]; voice uses handle 0x92C and skips 'Bgm' at name[0..2] when noFanfare (0x970)
fix: see golStartSystemSe / golStartVoice in RPGol_802b90b4.cpp
