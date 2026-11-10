# HID device API and power-management source-linked closure

RSPE01_01; codex-nearmiss-round3-1018; evidence build/evidence/round3/hid-{api,pm}/.

HID API's sole retained HID_DevInit function already scored100%; its26 instructions and symbolic operands match original. Source-linked full DOL equality permits Matching; unused upstream API routines/data are discarded.

HID power management's three original functions already scored100% and all892 raw function bytes match. The source lacked the hd_cb definition owned by its original BSS split. Defining tHID_DEV_CTB hd_cb in hidd_pm.c recovers324 bytes at8046FD30. Original split/symbol size328 includes four trailing alignment bytes; original HID_DevInit clears0x144 bytes, consistent with324-byte struct. objdiff BSS only reaches50% because symbol sizes differ; independently source-linked DOL equality proves required final BSS alignment and all code/relocations. Do not pad the struct or edit a shared header merely to inflate the section score.

Both source objects selected in main.elf dependencies; configured DOL SHA1 equals original8bb422971b88b5551a37de98db69557df7b46637. These are two new whole-object Matching completions, zero new100% function scores.
