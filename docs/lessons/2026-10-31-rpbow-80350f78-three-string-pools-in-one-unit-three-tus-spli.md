# RPBow_80350F78: three string pools in one unit = three TUs (split at 0x80351444 and 0x80351830)

- status: works
- tags: tu-split,splits,stringBase0,rodata,sdata2,RPBow
- scope: Pack/RPSports/RPBowScene/RPBow_80350F78
- source: claude/sp-50f78-20261031

symptom: unit .rodata = @stringBase0 + two 8-aligned lbl_ string blobs each used by one function (each containing its own 'RootPane'); .sdata2 had a 4-byte gap symbol at 0x804C695C; fn_8035170C/fn_80351B70 capped by blob offsets
cause: each blob is a separate TU's string pool (str reuse would have merged 'RootPane' in one TU); the sdata2 gap is TU-end padding to 8
fix: split text 80350F78-80351444 / 80351444-80351830 / 80351830-80351D58, rodata at 803934F8/80393520, sdata2 at 804C6958/804C6960; use plain literals; symbols.txt: pool sizes = string bytes incl. final NUL, not the padded size (0xE8->0xE3, 0x28->0x23, 0x58->0x57; 0x56 was one short and made dtk emit a gap_ symbol), delete gap_12_804C695C_sdata2. First third flipped Matching, DOL 0
