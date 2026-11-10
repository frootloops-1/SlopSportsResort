# dtk .s to CW asm converter

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBoxScene/RPBox_802e2a84

symptom: dtk .s to CW asm converter
cause: dtk .s to CW asm converter
fix: ~/Downloads/ogws-tools/s2cw.py <asm.s> <fn>: strips prefixes/@sda21(r0), .L_X->L_X; add extern C decls for mangled names by hand
