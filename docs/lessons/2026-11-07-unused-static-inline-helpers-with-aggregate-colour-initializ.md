# Unused static inline helpers with aggregate colour initializers still pool literals at parse time

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBsbScene/RPBsb_8024e9a4

symptom: Unused static inline helpers with aggregate colour initializers still pool literals at parse time
cause: Unused static inline helpers with aggregate colour initializers still pool literals at parse time
fix: delete unused ones (removed stray 0xFFFFFFFF entries from .sdata2)
