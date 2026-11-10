# cnt errorMap local-array template lands in .rodata, target .data

- status: open
- tags: data-section,rodata,local-aggregate,cnt,link-flip
- scope: revolution/CNT/cnt
- source: claude/nm-link-1 2026-10-15

symptom: revolution/CNT/cnt: all fns exact, .data 13% (688 B). Flip + DOL link: 609 symbols shifted +632 from 0x8037cb30 (DAYS_OF_MONTH).
cause: The function-local initializer template (0x278 B) is emitted to .rodata; orig cnt.o has no .rodata and .data=0x2b0 (template + 0x31 strings). The code copies the table to the stack, so it is a local aggregate, not a static.
fix: None yet. Tried: const local, non-const local (.rodata both), static const (.text 0x184, wrong), static non-const (.text -36 B), mw_version Wii/1.0-1.7 and GC/3.0a3/3.0a5.2 (template always .rodata; GC gives .text 0x1a8). Untested: #pragma section / __declspec(section) on a file-scope template + explicit memcpy, or a different -str/-rostr flag set.
