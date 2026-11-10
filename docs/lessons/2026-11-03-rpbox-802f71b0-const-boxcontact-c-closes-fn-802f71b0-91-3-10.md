# RPBox_802f71b0: const BoxContact* c closes fn_802F71B0 (91.3 -> 100); asm_diff.py does not rebuild

- status: works
- tags: constness,fn_802F71B0,scheduling,asm_diff,RPBox
- scope: Pack/RPSports/RPBoxScene/RPBox_802f71b0
- source: worker-1103d

symptom: fn_802F71B0 91.3, psq_l/ps_muls0 chain from c sits after the prologue mr/lwz instead of before stw r0; source-order variants of the BoxVecAddScale asm all gave the same 8 lines
cause: const pointee lets the scheduler float the r5-based loads; also tools/asm_diff.py reads the already-built .o and never rebuilds, so edit-then-asm_diff loops give stale results (use ninja first or verify.py/unit_cmp.py)
fix: fn_802F71B0(SbChild*, SbChild*, const BoxContact* c, f32); a small per-param const toggle loop (8 combos) found it in seconds; c_other gave 2 lines, c_c 0
