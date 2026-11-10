# Texture/Child pHeader identity: probe-verified colouring rules; no zero-cost construct found

- status: fails
- tags: regprobe,ef_animcurve,Texture,Child,pHeader,params,colouring
- source: xfer-1028 regprobe

symptom: target colours the pCmdList copy (mr r31,r3) first; ours colours it last (lowest) so tick+temp take r31
cause: Probes: parameter saved copies rank by argument index (newest first) regardless of uses; locals rank above parameters; every simple local copy of a param folds back to the param (rank lowest). Only a real merge (a ? (H*)a : 0) flips it, with an extra cmp/branch
fix: None zero-cost yet. Tried: aliases for each param, recasting at the two late uses, second header local, tables-before-mask (opcodes break), walking param (op 12, lines 67) or a copy (op 14, lines 44), const/volatile, out-param/accessor helpers. Next ideas: a join whose arms differ only in a value the compiler cannot prove equal without adding instructions; or locate why the original header copy is not propagated (a use after a call that clobbers?)
