# sda global lfs scheduled before LR save

- status: open
- tags: scheduling,prologue,rpbsb
- source: RPBsb_80273950 2026-10-16

symptom: fn_802744A0 97.1: orig lfs f0 global before stw r0 LR save
cause: unknown
fix: self->timer += global best; step-local variants worse
