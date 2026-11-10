# Game code (RP framework + Resort sports)

## Current state

- **RP framework (2026-11-09, batch 8):** 55 `Pack/` units (28 seeded + 27 carved). Matching: 17 of the 28 seeded
  plus carved IRPSysHostIOSocket. 3 MATCH-PENDING markers. Merge gates: `rm build/RZTE01_01/config.json` before
  `ninja`, `rm build/RZTE01_01/report.json` before regenerating it (symbol-only changes do not rebuild it),
  `tools/report_cmp.py`, then `sync_local_names.py --apply`. M4 95.4% (398/417). Still outside Pack/: RPSysSystem
  helpers 0x80237918/0x8023873C, RPSysStringUtility::ChangePoint, RPSysMiddleDB::GetRFLMiddleDB, Bowling gap
  0x804DDBE0-0x804E5100 (no unit).
  Resort layouts now in shared headers: EGG core (Thread, TaskThread, Xfb, XfbManager, Display, AsyncDisplay,
  ProcessMeter, Video), EGG::Scene (Disposer base, 0x30), EGG::ModelEx (0x10, no vtable), nw4r ef (EffectSystem
  0xC06C, DrawInfo 0xA0, CreationQueue, memory manager 0x3C).
- Next, by unit (scores from verify.py):
  - 2026-11-09 batch 11: RPSysParticleManager Matching (marker #29 cleared via inline reset()). RPSysHomeMenuMgr
    19/23 (absorbed unk/text_80242750: BanIcon, Unk_806F4D50); its last 4 need Resort KPADStatus 0xF0 in
    include/revolution/KPAD (ex_status 0x50 at 0x60, KPADMPStatus 0x3C at 0xB0, word 0xEC); also .data order
    (Unk vtable, jumptable, HomeMenuMgr vtable), extra 0.0f from weak EGG::Math<f>::zero, missing {7,"ScnRfl"} .rodata
    0x80666560; HBMCreateSound/HBMUpdateSound to declare in HBMApi.h. RPSysResourceManager 1/16: real file
    0x802317C8-0x80232768 (absorbs parts of unk/text_802315B8, unk/text_802325E0), LoadCompressed 4th arg, IsExist
    uses 0x58; header after 0x2C unreliable. RPSysCoreController::stopMotorAll 81 (renamed: 0x80240E18).
    EffectMgr 99.6 / EffectCreator 98.9 remain register colouring in inlined ef memory manager ctor.
    Bowling: rename lbl_806F4A08 -> sInstance__Q23EGG17CoreControllerMgr (RPBow_803547A4 extern).
  - 2026-11-09 batch 10: RPSysSystem, RPSysSceneMgr, RPSysScene Matching (weak `@STRING@Get<Name>__Fv` singleton
    strings, Resort layouts: EGG::Allocator 0x1C, HomeMenuMgr flags 0x4C-0x51 +0x40 shift, ResourceManager 0x5C/0x60).
    `RPSysEffectMgr.cpp` 63/64 and `RPSysEffectCreator.cpp` 17/18: createMemoryManager 99.6 / createSlowSystem 98.9,
    register residue from the inlined CalcMemorySize/ctor in include/nw4r/ef/ef_memorymanagerimpl.h (`size +=` fails).
    RPSysParticleManager 3/6 (0xC0 layout; Calc/CreateParticle need Unk_806B9908 getters 0x8024B564-0x8024B93C,
    fn_80244758 as methods; Initialize ledger #29). Next: RPSysHomeMenuMgr.cpp rewrite to the Resort layout
    (lbl_806F4D58 = spInstance, needs the RPGrpRenderer placeholder struct), RPSysResourceManager 1/16; Bsk/Swf to
    use GetStaticMem()/controller accessor so lbl_806B56A8/lbl_806B53E0 become @STRING@; fn_8035EC98 likely belongs
    to unk/sinit_8035EC9C. Bowling: 9 units Matching (batch 10 data pass).
  - `RPGrpModelImplement.cpp` 20/48, `RPGrpModelAnmImplement.cpp` 9/36: many 99.x are callee names only (fn_8024DE54
    RPGrpModel::CalcBeforeDraw, fn_8024E3DC Configure, fn_8024E46C/E42C ctor/dtor, fn_8016BC80/BBE0/C2D0/C230
    ResMdl::GetResNode/GetResMat, fn_802597A8 RPGrpModelRecord::Calc). Needs: nw4r ScnGroupEx, ModelEx::getResMdl
    0x801B4BB0 and method 0x801B43D0, nw4r expression-bodied accessors, ResAnm info +4, RPGrpModelAnm real base
    layout (8 x 0xC entries; replaces the 0x10 pad). Splits: AnmImplement .text 0x8024F018-0x80250BFC + .data
    0x806B9C30-0x806B9C50; ModelImplement .text from 0x80250BFC (absorbs unk/text_80250868).
  - `RPSysSaveDataMgr.cpp` 48/49: ctor 99.6 (sum pairing, parked).
  - `RPSysKokeshiManager.cpp` Matching. Debt: extern "C" fn_80262164 ("MsgResMgr"), fn_80246DEC.
  - Other splits to add: RPGrpModel .sbss 0x806F4DB8-0x806F4DE0, .bss 0x807CEE60-0x807CEE90; RPGrpModelRfl .sdata
    from 0x806F0C08, .bss 0x807CF008. eggStateGX: its .text ends 0x801A415C; the rest of StateGX (ColorUpdate 0x801A4160 .. fn_801A425C)
    sits in unk/sinit_801A2390.cpp, so an end at 0x801A4208 would cut StateGX in half (not 0x801A4208).
  - `RPGrpRenderer.cpp` 41/42, every section 100 but .text (batch 9b). Only blocker: `Rendering` 98.4,
    register-only (consts 1/2 at r30/r31 vs r22/r23); flip_gate links, DOL differs by 70 bytes, all in Rendering.
    7 source spellings failed (lessons). Markers #4 (volatile tables) and #5 (dead string-pool fn) remain.
    Resort RPGrpModelManager 0x60 and RPGrpModelScene (draw-path mgr 0x10, vptr 0xA8) layouts are in the headers;
    RPGrpModelManager ctor 41.8. lbl_806F4E18 (likely RPGrpModelScene::spAllocator) is unassigned.
  - Remaining seeded units not yet worked: RPSysResourceManager, RPSysHomeMenuMgr, RPBow_80323790.
  - Bowling (2026-11-09, split + 5 parallel lanes): 30 `Pack/RPSports/RPBowScene/` units, 248/415 fns exact
    (was 63). All code 100%: RPBow_80329350, RPBow_80347D0C, RPBow_8033FD0C, RPBow_80330EBC (+ Matching
    BallReturnRack, PinSetter); data/pools not checked, none flipped. Markers #6-#11 are Bowling (ledger).
    Cheapest next: a data pass (unit .sdata2/.rodata/.data ranges and Resort pool names) - dozens of 98.8-99.9
    functions have identical asm. Proposed splits: RPBow_80323790 .rodata from 0x80682200, .bss from 0x807D3BF8
    (gBowlingPhysicsData), .sbss from 0x806F5998; RPBowGlobalLaneManager .text from 0x804DE1B4 + .data
    lbl_806DED78; RPBow_80329658 pool ranges. Names: fn_801C052C -> __ct__Q23EGG8Vector3fFfff.
    Shared headers: RPUtlRandom.h getU32() out of line (weak 0x8025C9B0); eggController.h CoreController flags
    +0x1C, instance lbl_806F4A08; a header pulls a stray {0,2,1,3} .sdata2 constant with RPGrpModel.h;
    bowling.h SceneEntities +1 pointer before balls. Unwritten: RPBow_80323790 fn_804DB50C (0x13CC, ogws
    fn_803256C4), RPBowPlayerLaneNpc needs re-pairing; RPBowSwing fn_804E842C is a Resort rewrite.
    Bowling now spans 0x804C7B60-0x804FB3B8 in 45 units (bowling-rest: +RPBow_8032ADD8, RPBow_8032F514,
    RPBowObstacleManager, 12 Resort-only layout-UI placeholders RPBow_804F7864..RPBow_804FADAC; 63+ new exact).
    Not in Resort: ogws UI files (8034F710..80354CAC), pin/obstacle training modes (80335DB0, 803433E4).
    Not found near Bowling: 80313028 (RPBowScene class, likely with RP scene code), 80315998, 8031C388,
    803349E0, 8034C1AC. Neighbours: 0x804FB3B8+ is Basketball, 0x80489030-0x804C17A8 is Canoeing.
    Left in unk/: text_804C17A8 (score UI, cut by string pools/vtables like 804F2830), text_804D1D1C,
    text_804DE040, text_804E54D8 (tail 0x804E7558 ~ ogws RPBowPlayerLaneNpc: re-pair target), text_804FA71C
    (obstacle-related, start unknown). ~34 MI thunks unwritten (need layout class hierarchy). bowling.h fixes
    for UpdateBallsMdl: balls ptr 0x34, ballMtx 0x2BEC, phys field 0x118; lbl_807D3BF8 = gBowlingPhysicsData.
  - Archery (2026-11-09): `src/Sports2/Arc/`, 25 units over 0x805479BC-0x8057E310, 219/857 exact (first pass:
    accessors, empty virtuals, singleton create/destroy, tail calls). File names from singleton strings (Analyzer,
    Camera, Field, TargetMgr, AvatarMgr, SequenceMgr, ObjMgr, Wipe, SignMgr, EffectMgr, ObstacleMgr,
    BonusTargetMgr); others `Arc_<addr>` (scene 805479BC, arrows 80549568, 9 layout files 8057750C-8057C790).
    Namespace unproven: symbols keep fn_ names; first-pass sources use extern "C" placeholders. 10 creates at 97%
    only differ by the name's string-pool offset (pool recovery). Arc_80571BC8 is probably several files.
    Neighbours: unk/text_80547010 is Basketball; unk/sinit_8057E310 is Power Cruising/Wakeboarding.
  - Power Cruising + Wakeboarding (2026-11-09): one engine. 61 units over 0x8057E310-0x805B5FD8, 245/1185 exact
    (generated first pass: leaf accessors, setters, tail/vtable calls, simple ctors). `src/Sports2/Jsk/` 23 units
    (rings, buoys, balloons, HUD + 65xxx_jsk layouts), `Sports2/Wkb/` 11 (tow boat, corners, boat avatars, goal
    flags, 66xxx_wkb layouts), `Sports2/JskWkb/` 27 shared (scene 0x806E5360, cameras/env, collision, player,
    avatar, vehicle; `JskWkb` is an invented placeholder dir). No names proven (no singleton strings); 0 renames.
    Factory-created classes (80587A3C, 80588A6C, 80598140, 805A4334) placed here weakly (fn_8033D45C serves other
    sports). Unwritten: 61 MI thunks, ~25 layout ctors (string-pool offset), layout/MI dtors, all game logic.
    unk/sinit_805B5FD8 (0x805B5FD8-0x805B65D8) is Frisbee Dog.
  - Pool pass (2026-11-09): +50 exact over Bowling/Archery/JskWkb (779 -> 829). bowling.h SceneEntities +1 ptr,
    LaneContext.throwContext 0x2BEC, phys field 0x118; gBowlingPhysicsData/gLaneXOffsets named; RPUtlRandom getU32()
    out of line (Bowling-only includer). Still blocked on unwritten pool users: Archery creates Camera/Field/
    SequenceMgr/SignMgr/BonusTargetMgr (see users fn_805570D4, fn_8055C3E4, fn_8056EF28, fn_80574EDC, fn_8057CDC8);
    Arc_80577838/80578790/8057B014/8057C020 layouts; several Wkb/Jsk layouts. BowCamera (RPBow_80319C98) needs a
    full Resort re-derivation. fn_8020B108 = MTX34 copy ctor (rename in its unit). Marker #12 is a Jsk pool seed.
  - Basketball (2026-11-09): `src/Sports2/Bsk/`, 68 units over 0x804FB984-0x805479BC, 537/1672 exact (first pass,
    extern "C" placeholders on raw offsets). Proven: namespace Bsk, `Bsk::Scene` (vtable 0x806DFE80; dtor and @48
    thunk renamed; derives from RPSysScene via an unnamed intermediate). Singleton strings: GraphManager, Config
    (probable Bsk::, symbols not renamed). 20 layout files named by 65xxx_bsk_ resource in their header comments.
    ~45 functions at 97-99.9 are pool offsets only; parked: fn_8050F258/F300 (branch shape), fn_805017C4 (struct
    copy order), fn_804FD9E4 (arg order), fn_80503B30 (regs). Unwritten: ~33 MI thunks, deleting dtors, branchy
    game logic. RPBow_804FB3B8 (0x804FB3B8-0x804FB984) is Bowling.
  - Canoeing (2026-11-09): `src/Sports2/Can/`, 48 units over 0x80489030-0x804C17A8, 395/1114 exact. Singleton
    file names (probable): Config, PlayerMgr, FieldMgr, SequenceMgr, Main, VSMgr; 12 655xx_can layouts. No namespace
    proven (no scene string here). Other can units (0x803CD33C, 0x803FF70C, 0x804075C0, 0x804344D8) not carved.
    unk/text_804C17A8 starts with 5 Canoeing VS layouts (65511-65515) before Bowling score layouts: split it.
    ~30 fns 97-99.7 are pool residues; 9 layout ctors at 96.5 (strncpy scheduling, dead end).
  - Frisbee Dog (2026-11-09): `src/Sports2/Fld/Ddg/`, 38 units over 0x805B5FD8-0x805EFD7C, 373/1081 exact. Proven:
    `Sp2::Fld::Ddg::Scene` (qualified singleton string; ctor/dtor renamed). RingMgr probable. 0x805EFD7C-0x805F181C
    is Swordplay (unk/sinit_805EFD7C, sinit_805F0C58). Shared state-machine template (fn_803457F4 family, ~100 weak
    copies here, also in Arc/Bsk) wants one shared header.
  - Swordplay (2026-11-09): `src/Sports2/Swf/`, 95 units over 0x805EFD7C-0x80653FA0 (end of .text; the unsplit tail
    after the last __sinit is Swordplay too), 850/1994 exact (lanes 306/713, 237/546, 307/735). No names proven: no
    singleton creates or qualified strings; classes carry Shift-JIS getName strings (薪割り Speed Slice, 対戦 Duel,
    組み手 Showdown) used in header comments only. Markers #18 (file-scope auto_inline off, 9 files) and #19
    (dont_inline regions, 4 fns). Debt: 8 files declare `__ct__Q34nw4r4math4VEC3Fv` in extern "C" (Resort calls the
    VEC3 ctor out of line; ogws header inlines it - fix the shared header), `sCurrent__13RPGrpRenderer` declared as
    extern char[]. Open: .sbss lbl_806F6040 (written by Swf_8063348C and Swf_80602BD4) unassigned; state-machine
    copies not adopted yet (Swf_8060CB6C, 805F0C58, 8060E6E4, 806108AC, 8063269C, 806457E0, 80650440); ~40 MI
    thunks, ~25 layout/MI deleting dtors, all __sinits, pool-offset near misses, game logic.
  - State-machine template (2026-11-09): include/Sports2/Unk_StateMachine.h (`Unk_StateMachineBase` 0x20 + vtable,
    `Unk_StateMachine<T>` with enter/exec/exit PTMF tables; placeholders, no RTTI/strings). Base unit
    `Sports2/Unk_803456D0` 9/9 (carved from unk/sinit_80344DC4 -> text_80344DC4 + sinit_80345820). 34 owners in
    Ddg/Arc/Bsk/Can/Jsk/Wkb, all copies exact (+~250); names `__ptmf_null`, `__ptmf_cast`,
    `__dt__20Unk_StateMachineBaseFv` (0x801ED018). Marker #28: file-end explicit instantiations stand in for
    unwritten owner code (remove per line as callers are written). Owners named `Unk_<first vtable>`; must be
    polymorphic. Retail emission order of the copies not reproduced (needs real owner code before any flip).
  - Bowling units keep ogws-port debt (vtable as a data table, extern "C" fn_80372C18/fn_8037307C/fn_80372FD8).

- First game unit Matching: `Pack/RPGraphics/RPGrpDrawPathShadowTexture.cpp` (ogws source, unchanged), DOL OK.
- Build setup (configure.py): lib `RP`, `Wii/1.0`, `cflags_rp` from ogws + **`-func_align 4`** (Wii/1.0 otherwise
  aligns C++ functions to 16; Resort packs them at 4), PCH `include/SportsPack.pch` -> `SportsPack.mch`.
  `-DVERSION_RSPE01_01` is defined so ogws headers take their Wii Sports Rev 1 branches.
- Porting a unit: compile, `tools/obj_score.py`, `tools/complete_split.py` for data, `tools/resolve_externs.py`
  (JSON list of units) for names the source expects, then `ninja` + `tools/dol_blame.py`.
  Weak inline copies (base-class methods, header inlines) only dedupe if Resort's own copy carries the real name.
- `RPGrpViewRender2D.cpp`: 6/7 exact. Resort's `RPGrpView` gained a 4-byte member at 0x1C (vtable moved to 0x20);
  its ctor `__ct__9RPGrpViewFUc` (0x80255F64, 0xA8 vs ogws 0x58) is rewritten. Needs the header change and
  `RPGrpView.cpp` matched first.
- `RPGrpDrawPathLightMap.cpp` 4/5, `RPGrpCaptureTexture.cpp` 1/2 (scan, not yet looked at).
- Only 9 ogws Pack units have Resort splits; RP framework code mostly sits in `unk/sinit_*` and auto units.
  197 RP function names are known (fuzzy match).
- Resort's own sports code: no names yet. Class-name strings (`docs/class_strings.md`): `Sp2::Fld::Ddg::Scene`,
  `Bsk::Scene`, `Nkm::SceneBase`, `Doh::DrawGX/Memory/ResourceManager/CollisionManager`, `Cmn::MapDataManager`.

- Resort-only code: `tools/sport_map.py` attributes units to sports from `WS2_<code>_` resource strings
  (`docs/sport_map.md`; codes swf wkb fld arc bsk png glf bwg can bic pln jsk dgl omk). Rough layout:
  omk/glf/dgl ~0x801C-0x8040, bic/can ~0x8038-0x805A, pln 0x8042, png 0x8045, bsk 0x804F-0x8053,
  arc 0x8055, jsk 0x8059, wkb 0x805A, swf 0x805F-0x8064.
- First Resort-only source: `src/unk/sinit_8051B8B4.cpp` (Basketball), lib `Sports2`, NonMatching.
  3/11 functions matched (Reset, a setter, deleting dtor of placeholder class `Bsk::Unk_806E0ED0`).
  With `-inline deferred` MWCC emits functions in reverse source order: define them last-first.
  `lbl_807D1558` is a 12-byte .bss vector used 500+ times (maybe `EGG::Vector3f::zero`, unconfirmed).
- `Unk_8051BB0C` (0x29C, collision/contact check over two hands/points, calls `fn_8050C6C4`) is fully
  reconstructed at 95.4%: same logic, 166 vs 167 insns. Remaining: original indexes `m24[i]` as
  `this + i*12` (mine strength-reduces to a pointer) and swaps the stack slots of `push` and the scaled
  `mUnk34` temporary; regalloc follows. Tried: hoisted table pointer + `maxLen` local (kept, they fixed
  the f30/r28 hoists), inline accessor for `m24[i]`, `push` declared at loop top, named temporaries,
  byte-offset indexing (all worse or equal).
- Resort's math is paired-single NW4R (`VEC3Sub/VEC3Scale` inline asm, `VEC3Len` -> `PSVECMag`);
  ogws's EGG vector operators are scalar, so use `nw4r::math::VEC3` for Resort code.
- Tools: `tools/fn_asm.py <fn>` (asm with float/string values), `tools/fn_diff.py <unit src> <fn>`
  (rebuild + normalised instruction diff).
- objdiff pairs functions by name: rename the Resort symbol to the mangled name you write.

- **Game-code flags (2026-11-09):** Wii/1.3 (not 1.0) and `-pragma "optimize_for_size on"` on top of ogws
  cflags_rp. Size mode is what turns MTX34 copies into `lwz/lwzu/bdnz` loops and 3-register prologues
  into `_savegpr_29`. RPGrpDrawPathShadowTexture stays 7/7.
- Basketball unit `unk/sinit_8051B8B4.cpp`: exact: Reset, SetUnk4, dtor, Unk_8051BF34, Unk_8051BDA8.
  Unk_8051BB0C 167/167 insns, stack-slot/regalloc only. Unk_8051C51C 149/156 (original precomputes
  table element addresses). Not written yet: fn_8051B8B4 (effects via `RPSysEffect`, copies
  `lbl_807D1598` = likely `EGG::Matrix34f::ident`), fn_8051C0F4, the inline ctor, the __sinit name.
- Levers that worked here: member-wise vector fill instead of the 3-arg ctor; declaring locals in
  the order of their stack slots; a named local for a constant reused after a call (`f32 rate`).

## Next

1. Match `RPGrpView.cpp` with the new member, then `RPGrpViewRender2D.cpp`.
2. Split the RP framework TUs inside `unk/` using the 197 known RP names and ogws's splits (port_splits with a
   lower coverage threshold, checked by hand).
3. Pick one small Resort-only sport/system (start from a class-name string) and name/match it.
