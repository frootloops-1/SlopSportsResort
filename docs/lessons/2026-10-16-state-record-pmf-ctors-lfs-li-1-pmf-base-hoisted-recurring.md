# state-record PMF ctors: lfs/li -1/PMF base hoisted (recurring)

- status: open
- tags: ctor,ptmf,scheduling,rpbsb
- source: RPBsb_802803b0 2026-10-16

symptom: fn_80281424 76.2, fn_8026FF28 73, fn_80285398 87.3
cause: unknown source shape of the shared state-record base
fix: dead ends: swapped stores, inline reset(), init() first. Next: match base ctor fn_80272D70 in RPBsb_8027039c
