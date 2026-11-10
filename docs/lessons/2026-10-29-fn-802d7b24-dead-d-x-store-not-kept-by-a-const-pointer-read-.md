# fn_802D7B24: dead d.x store not kept by a const-pointer read either

- status: fails
- tags: fn_802D7B24,RPBox_802cf93c,dead-store
- scope: RPBox_802cf93c
- source: claude/box802cf-r4-1029 opus

symptom: retail keeps stfs d.x twice (0x98); ours deletes the first in the PCode optimizer (present in backend-00 initial code, gone after optimizer)
cause: the local-memory dead store is removed after VN forwards the d.x load; retail's first store is either to a different object/alias or the read is not forwarded
fix: failed: d.x = ((const BoxV3Pod*)&d)->x * 0.8f (still one store, 98.7). Untried: first store through an escaped pointer whose IRO copy is not propagated, separate temp object sharing the slot
