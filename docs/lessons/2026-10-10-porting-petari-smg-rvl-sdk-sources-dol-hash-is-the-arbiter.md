# Porting Petari (SMG) RVL_SDK sources: DOL hash is the arbiter

- status: works
- tags: petari,port,gx,dol

symptom: objdiff shows 100% .text but sdata/sbss/data sections <100% (padding, symbol naming, jump tables)
cause: dtk rounds split section ends to 8 and names data differently; objdiff section % is not authoritative
fix: Flip to Matching, run 'ninja build/RSPE01_01/ok'; diff main.dol vs orig with a DOL range script. Petari GX needs: vendored private/*_reg.h + shortcut_*.h, widened GXData (union aliases), VI_TVFORMAT_* instead of VI_*, s16 interrupt handlers, remove functions absent from the binary, GX_TF_A8 alias bug (use GX_CTF_A8), version strings differ
