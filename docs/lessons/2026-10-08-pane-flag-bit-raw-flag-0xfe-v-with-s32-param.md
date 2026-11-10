# Pane flag bit: raw (flag & 0xFE) | v with s32 param

- status: works
- tags: mwcc,bool,pane-flag

symptom: SetVisible(u8) adds neg/or/srwi normalisation; !type emits extrwi
cause: u8 param and bool normalisation
fix: static inline SetPaneFlag0(Pane*, s32 v) writing pane+0xB7 raw
