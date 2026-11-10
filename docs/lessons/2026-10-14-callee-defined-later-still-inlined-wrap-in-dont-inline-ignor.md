# Callee defined later still inlined: wrap in dont_inline; ignored pointer arg still stored on caller stack

- status: works
- tags: inline,dont_inline,bss,static
- source: RPBsb_8027b7a0

symptom: caller 29% because callee inlined; standalone copy also emitted
cause: -inline auto inlines callee defined in same TU
fix: #pragma dont_inline on/reset around callee; unnamed const u32* param for ignored arg (caller still stores local on stack); function-local static u16 buf[32] in non-inlined helper gives 0x40 .bss with no guard; merge split rodata pool in symbols.txt (0x8038D138..D230 -> size 0xF8) clears phantom addi
