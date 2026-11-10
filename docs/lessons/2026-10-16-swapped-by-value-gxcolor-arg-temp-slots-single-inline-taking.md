# Swapped by-value GXColor arg temp slots: single inline taking colour by value

- status: works
- tags: stack-layout,gxcolor,inline,rpbsb
- scope: RPBsb_8027c2f0,RPBsb_8028aef0
- source: claude/rpbsb-3

symptom: Two by-value GXColor temp copies land at swapped stack slots (99.9%)
cause: Each call copied the global separately; the original's colour is an inline param at sp+8 with copies 0xc then 0x10
fix: Put both draw calls in one static inline taking the colour by value, call once with the global (or build colour from alpha inside). Failed: block scopes, per-call inlines, derived type w/ dtor, named c1/c2, loop.
