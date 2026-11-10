# fn_80281DA0 (RPBsb_802817a0) 99.7 -> 100: return the score (f1 stays live past fctiwz)

- status: works
- tags: rpbsb,fpr,fctiwz,return-type,signature,mwcc_dbg
- source: claude/bsb-1a88-1103f bfc37dc6e

symptom: Conversion temp lands in f1 and diff in f2 (retail: temp f2, diff f3)
cause: FPR allocator colours highest vreg first; score dies at the conversion so its temp reuses f1. Retail's f1 stays occupied because the function returns score
fix: void -> f32 and return score; (definition and forward decl); only caller ignores the result. Signature inferred from regalloc, not a steering construct, no marker. General: a local whose conversion temp sits one FPR too low with the local in f1 may be the return value
