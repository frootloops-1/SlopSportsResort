# BsbScn ctor fn_8026FF28 state-init dead ends

- status: fails
- tags: ctor,ptmf,regalloc,rpbsb
- source: RPBsb_8026eccc 2026-10-16

symptom: 71.9: state 0 PMF values get callee-saved regs, shifted one state vs original
cause: virtual-register order; source shape unknown
fix: dead ends: init(const&) 41, member store orders other than obj,a,b, nested set(), reset() inline/loop, named PMF locals; zero-store placement grid reaches 73.0 only by unfaithful order. Next: match base ctor fn_80272D70 in RPBsb_8027039c first
