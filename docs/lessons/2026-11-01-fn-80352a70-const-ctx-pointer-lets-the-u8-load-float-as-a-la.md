# fn_80352A70: const ctx pointer lets the u8 load float as a late temp

- status: works
- tags: const,scheduler,fn_80352A70,RPBow
- scope: Pack/RPSports/RPBowScene/RPBow_80351D58
- source: step2 2026-11-01

symptom: 98.8%: dbl local got a low named vreg (r4 vs r0)
cause: a u8 load through a non-const ctx pointer cannot move above the anim stores; with const the pre-RA scheduler floats the lbz up as a late codegen temp coloured first
fix: const BowCtx* pCtx, drop maxFrame/dbl locals, test pCtx->getField55() inline; also symbols: lbl_80393578 -> @stringBase0 size 0x244, @417/418/421 renamed @420/421/424. Tooling: mwcc_dbg.sh hard-codes gdb port 9001, concurrent workers collide (check the Reading /private/tmp/<worktree> line in run.log)
