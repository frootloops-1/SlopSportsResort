# li rZ,0 stored then li rM,K; beq; mr rM,rZ: the two arms are ENUM-typed constants (x = c ? E0 : E7), not int

- status: works
- tags: enum,ternary,constant-propagation,mr,zero-reuse,rpgol,802bca94,802bb608
- source: worker gol-manual 2026-10-31

symptom: 99.5%: target stores a zero byte then reuses that register via mr r0,r3 for the m=0 arm; ours re-materialises li 0 with r0/r3 swapped
cause: with plain int constants MWCC either re-materialises (m=7; if(c) m=0) or emits branchless neg/or/srawi/andc; with enum-typed arms it skips the select conversion and reuses the live zero register
fix: file-local enum GolShotMode {0, 7}; res->s7C = r ? GOL_SHOT_MODE_0 : GOL_SHOT_MODE_7. Found via RFLiGetCharInfo (RFLErrcode return reuses the '\0' store zero). Fast lever check: compile a minimal .cpp with the unit's exact mwcceppc flags (ninja -t commands). Dead: shared z variable/bool/chained = (constant-propagated), int ternary 94.3.
