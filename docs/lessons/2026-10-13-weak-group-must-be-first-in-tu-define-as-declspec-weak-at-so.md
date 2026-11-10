# Weak group must be first in TU: define as __declspec(weak) at source end

- status: works
- tags: weak,order,vtable,RPSysTagParms
- scope: RPSysTagParms
- source: sonnet

symptom: 12/12 fns exact but DOL FAILED: inline virtual dump/write/read of base class (weak) sat at TU end in R,W,D order; original has them first in D,W,R
cause: in-class or outline inline weak virtuals are emitted after strong fns; DECOMP_FORCEACTIVE and moving ctors did not help; also out-of-line add/getTag helpers must be marked inline or they are emitted as extra globals
fix: declare virtuals in header without body; define __declspec(weak) void C::read(..){} then write then dump at END of the cpp (reverse emission puts them first as D,W,R); mark helper defs inline
