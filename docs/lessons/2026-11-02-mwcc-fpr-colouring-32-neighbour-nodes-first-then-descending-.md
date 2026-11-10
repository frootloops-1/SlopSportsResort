# MWCC FPR colouring: >=32-neighbour nodes first, then descending vreg; lowest used callee-saved reg reused

- status: works
- tags: regalloc,fpr,colouring,mwcc_dbg
- scope: general

symptom: node with free f31 still got f30
cause: assigned.txt order: nodes with >=32 interference neighbours (dist 33, t 69; one at 31 was NOT early) are coloured first, rest by descending vreg; a node takes the lowest-numbered already-used non-conflicting callee-saved register, else the next new one from f31 down
fix: To get a value onto f31 it must interfere with the register already used (f30 holder) or colour before it; make early values inline-expansion temps (higher vreg) rather than named locals
