# Marker ledger

Markers are source constructs that steer MWCC to the original bytes without being plausible original source
(decomp-code-rules Section F / R17): identical-arm ternaries, dead pool-order literals, dummy locals, invented
helper boundaries, extra functions, steering casts. Policy (user-approved 2026-10-26):

1. Last resort: try the structural levers first (helper boundary, const parameter, branch shape, direct constructor body,
   array + loop, definition placement). Use a marker only when nothing else closes the function.
2. Every marker has an adjacent `// MATCH-PENDING (R17): <what it steers and why, what the real source probably lacks>` comment.
3. Invented helper names get `// name inferred` and a generic name.
4. This ledger is updated in the commit that introduces the marker.
5. Gate: verify.py no regression, DOL 0 bytes, sym_addr_check only the 4 known collisions. Revert a marker that fails.
6. Reports count marker functions as "bytes-matched, MATCH-PENDING", never as plain matches.

Scores are objdiff function scores. A unit listed as flipped to Matching contains the marker(s) shown.

(Resort ledger, started 2026-11-09. ogws history stays in the ogws repo.)

| # | Function | Unit | Status | Marker | Why |
|---|---|---|---|---|---|
| 1 | `Unk_8024CC84__11RPGrpCameraFv` | Pack/RPGraphics/RPGrpCamera.cpp | bytes-matched, MATCH-PENDING | `*(volatile u16*)&mFlags.all` reads | original reloads the flag halfword for each test (lhz twice); plain mask read loads once (98.5%), bitfield read gives extrwi (97.8%) |
| 2 | 4 functions using 1.0f/-1.0f/0.0f | Pack/RPGraphics/RPGrpCamera.cpp | bytes-matched, MATCH-PENDING | dead `static void PoolSeed(f32*)` at file end | .sdata2 pool order (pooled in emission order; -inline deferred emits the last definition first); without it 10/14, DOL 55 bytes off |
| 3 | `Calc__Q29RPGrpView7ClipperFPC11RPGrpScreen` | Pack/RPGraphics/RPGrpView.cpp | bytes-matched, MATCH-PENDING | named local `f32 one = 1.0f` as the reciprocal numerator | f0/f1 colouring of the 1.0f constant vs tanFovy swapped (99.6%); static inline reciprocal, FInv, local tan/near/inv, declare-then-assign all failed; original probably used an inline math helper not yet identified |
| 4 | `fn_80254AE8` | Pack/RPGraphics/RPGrpRenderer.cpp | MATCH-PENDING (99.9%: remaining diff is the unnamed fn_801A4208 = StateGX::GXSetDither_) | `static const volatile u32` group tables | original reloads table[idx] after each call; plain/extern/file-scope const tables are CSE'd (93.7%), non-const ones reload but land in .data; tables are in .rodata so they were const |
| 5 | (dead) `RPGrpRenderer_GetDrawSceneName` | Pack/RPGraphics/RPGrpRenderer.cpp | steers .rodata | invented function using "2d"/"3d"/"3dAfter"/"3dFree" | the string pool (0x80666B68) starts with these four names whose user was dead-stripped; without it fn_80254A18's pool offsets are off by 0x15 |
| 6 | (dead) `BowCam_StrippedDebug` | Pack/RPSports/RPBowScene/RPBow_80348158.cpp | steers .sdata2 (unit NonMatching) | invented function returning x + 40.0f | the 40.0 at the head of the unit's .sdata2 belongs to a dead-stripped function whose body is unknown |
| 7 | (dead) `BowCam_StrippedFovy` | Pack/RPSports/RPBowScene/RPBow_80319C98.cpp | steers .sdata2 (unit NonMatching) | invented SetFovy + s32->f32 function | 0.0/180.0/0.5/256/360/int-to-float magic lead .sdata2 ahead of fn_804CAB84's constants; their user was dead-stripped |
| 8 | `fn_804D39F0` | Pack/RPSports/RPBowScene/RPBowNpcManager.cpp | bytes-matched, MATCH-PENDING | `#pragma dont_inline on/reset` around the helper | retail keeps the small state setter out of line; the deferred inliner folds it into ActivateNpcTurn otherwise |
| 9 | `__dt__` of RPBowTrajectoryGuide, RPBowBackgroundNpcManager, RPBowMotionBlur | Pack/RPSports/RPBowScene/ | bytes-matched, MATCH-PENDING | dtor written as `extern "C"` free function with the mangled name | Resort dtors call no base dtor; recover the real class hierarchy (trivial base dtors) and write them as member dtors |
| 10 | `fn_804DA64C`, `fn_804DC924`, `fn_804DC998`, `fn_804DCA60`, `fn_804DCC60`, `fn_804DCEAC`, `fn_804DCF18`, `fn_804DD040` | Pack/RPSports/RPBowScene/RPBow_80323790.cpp | bytes-matched, MATCH-PENDING | `#pragma use_lmw_stmw off` around each | these save GPRs with stw pairs where the unit's own functions use stmw (struct copies still use size-mode word loops, so not optimize_for_size off); they look like header inlines / copy operators emitted out of line under other settings. Without the pragma: stmw (37-90%) |
| 11 | `fn_804DB220` | Pack/RPSports/RPBowScene/RPBow_80323790.cpp | bytes-matched, MATCH-PENDING | `static inline` BowMul / SpeedMag helpers | BowMul keeps `sp * k` fmuls operand order; SpeedMag (returns f64) gives the frsp after fn_80204FEC. Nothing else in the unit is inlined, so the real source differs |
| 12 | (dead) `sIllustName`, `sPaneNames` | Sports2/Jsk/Jsk_805B53C8.cpp, Sports2/Jsk/Jsk_805AC80C.cpp | steers .rodata (units NonMatching) | unused file-scope `static const char*` / array whose literals pool first | the layout file's string pool starts with pane names no written function uses; inferred as a dead-stripped header table, not proven |
| 18 | small same-file callees (first pass) | Sports2/Swf/Swf_80615BEC, 80621738, 8061F194, 80629B98, 80625D00, 8062AA6C, 8062BB8C, 8062C234, 8062CB80 | units NonMatching | file-scope `#pragma auto_inline off` | retail calls these callees out of line; the real cause (inline keyword/definition order/size) is not recovered. Remove once callers match without it |
| 19 | `fn_80614FD0`, `fn_80627C34`, `fn_8062BBC0`, `fn_8062C820` | Sports2/Swf/Swf_80614864, 80625D00, 8062BB8C, 8062C234 | units NonMatching | `#pragma push` / `dont_inline on` / `pop` around the callee | same as #8: retail keeps the small helper out of line; find the authentic reason |
| 28 | `Unk_StateMachine<Unk_*>` ctor / setState / calc copies (34 owners) | Sports2/Arc, Bsk, Can, Fld/Ddg, Jsk, Wkb (34 units) | bytes-matched copies, units NonMatching | file-end `template ...;` explicit instantiations of the state-machine members | retail instantiates them implicitly from the owner ctor / update functions, which are not written yet; remove each line once its caller is written (emission order then follows the real callers) |
| 30 | `fn_804E5018` | Pack/RPSports/RPBowScene/RPBow_80329658.cpp | bytes-matched, MATCH-PENDING (unit NonMatching) | free function calling `__ct__Q34nw4r4math4VEC3Fv` by hand 19 times | real source is a class ctor with VEC3 members; class layout not modelled yet |
