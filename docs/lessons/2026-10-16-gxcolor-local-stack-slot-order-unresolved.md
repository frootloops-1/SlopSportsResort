# GXColor local stack slot order unresolved

- status: open
- tags: stack,gxcolor,rpbsb
- source: RPBsb_8028aef0 2026-10-16

symptom: fn_8028B610 99.7: orig local at sp+8, by-value temps at 0xc/0x10; ours reversed
cause: unknown; declaration order/const variants didn't move it
fix: untried: permuter, temp struct copies explicit
