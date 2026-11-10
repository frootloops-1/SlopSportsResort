# base ctor PMF temp stack-slot direction

- status: open
- tags: ctor,ptmf,stack,rpbsb
- source: RPBsb_8027039c 2026-10-16

symptom: fn_80272D70 70.6: orig PMF temps descend (state 0 highest), ours ascend; orig hoists lfs 1.0/0.0/PMF base into state 4 init
cause: unknown
fix: dead ends: reversed statements, param order, const-ref (55), named PMF locals, nested blocks, inline initStates(), array member
