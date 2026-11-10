# Volatile-GPR colouring sim (lowest free r0/r3..r12 in dump order) reproduces MWCC exactly; use it to find which CSE temp must colour first

- status: works
- tags: regalloc,gpr,sim,cse,RPBow_80319C98
- scope: general

symptom: two volatile GPR families swapped (k-rows vs (j+1)*16)
cause: colour order = descending vreg; front-end CSE temps numbered at their 2nd use
fix: tools/regalloc_sim/vsim.py + vexp.py <assigned.txt> "n=name,..." "A<B" (move node A before B, recolour): showed (j+1)*16 must colour before base+k*16 in fn_8031A0E0; 0 mismatches on two dumps
