# DrawPathBase @112@ thunk order (dt vs scnProcDraw) reversed: unsolved

- status: works
- tags: thunk,vtable,multiple-inheritance
- scope: egg/gfxe

symptom: eggDrawPathBase 9 DOL bytes: @112@__dt__ and @112@scnProcDraw thunks swapped, vtable slots swapped
cause: implicit dtor of DrawPathBase (ScreenEffectBase + IScnProc); explicit inline dtor in header changed nothing
fix: open. O1 (Opus, 2026-10-15, claude/nm-weak-1) dead end: explicit out-of-line ~DrawPathBase() in the .cpp, before or after scnProcDraw (FORCEDTOR helper removed), fixes strong order but thunk order stays @112@scnProcDraw, @112@__dt__ (ours = reverse vtable slot order, orig = slot order); it also stops DrawPathHDR::__dt__ inlining the base dtor (100 -> 93.5). Untried: key-function change, how thunks are queued (e.g. a use of the dtor thunk before scnProcDraw is compiled).

SOLVED 2026-10-27 (marker): unreferenced derived class FORCETHUNKeggDrawPathBase pre-creates the scnProcDraw thunk; see marker ledger row 23.
