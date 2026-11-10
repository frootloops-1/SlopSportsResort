#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "RZTE01_01",  # 0
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--ninja",
    metavar="BINARY",
    type=Path,
    help="path to ninja binary (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--warn",
    dest="warn",
    type=str,
    choices=["all", "off", "error"],
    help="how to handle warnings",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.ninja_path = args.ninja
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-2"
config.compilers_tag = "20251118"
config.dtk_tag = "v1.8.3"
config.objdiff_tag = "v3.6.1"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.3"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-g")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
    "-i include",
    "-i include/MSL",
    "-i include/MSL/internal",
    f"-i build/{config.version}/include",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
    # Headers/sources ported from ogws branch on Wii Sports revisions; Resort's libraries are
    # newer than Wii Sports Rev 1, so select the Rev 1 side.
    "-DVERSION_RSPE01_01",
    "-ir include/revolution/BTE",
    "-DREVOLUTION",
]

# Debug flags
if args.debug:
    # Or -sym dwarf-2 for Wii compilers
    cflags_base.extend(["-sym dwarf-2", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Warning flags
if args.warn == "all":
    cflags_base.append("-W all")
elif args.warn == "off":
    cflags_base.append("-W off")
elif args.warn == "error":
    cflags_base.append("-W error")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline auto",
]

# Flag blocks follow ogws (Wii Sports). Compiler versions come from tools/compiler_sweep.sh:
# Wii/1.0 scored best for NW4R, EGG, the RVL SDK and MSL; the Bluetooth stack (BTE) and
# RVLFaceLib are prebuilt older libraries that match GC/3.0a5 / GC/3.0a5.2.
cflags_pedantic = [
    "-w unused",
    "-w missingreturn",
    "-w hidevirtual",
    "-w filecaps",
    "-w sysfilecaps",
    "-w tokenpasting",
    "-w impl_float2int",
    '-pragma "warn_no_explicit_virtual on"',
    "-w err",
]

# RVL SDK flags
cflags_rvl = [
    *cflags_base,
    "-enc SJIS",
    "-fp_contract off",
    "-ipa file",
]

# NW4R flags
cflags_nw4r = [
    *cflags_base,
    *cflags_pedantic,
    "-enc SJIS",
    "-fp_contract off",
    "-ipa file",
    "-i include/nw4r",
]

# EGG flags
cflags_egg = [
    *cflags_base,
    "-enc SJIS",
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-i include/nw4r",
    "-ir include/egg",
]

# RP (Sports Pack game framework, shared with Wii Sports) flags
cflags_rp = [
    *cflags_base,
    *cflags_pedantic,
    "-DPACK_SPORTS",
    "-func_align 4",
    # Resort game code was built optimising for size: struct copies become word loops and
    # 3-register prologues use _savegpr (found on unk/sinit_8051B8B4.cpp; RP units unaffected)
    '-pragma "optimize_for_size on"',
    "-enc SJIS",
    "-inline deferred",
    "-fp_contract on",
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-i include/nw4r",
    "-ir include/egg",
    "-i include/Pack",
]
cflags_rp_pch = [*cflags_rp, "-prefix SportsPack.mch"]

config.linker_version = "Wii/1.0"


# Helper function for Dolphin libraries
def DolphinLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": objects,
    }


# Helper function for REL script objects
def Rel(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.3.2",
        "cflags": cflags_rel,
        "progress_category": "game",
        "objects": objects,
    }


Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.precompiled_headers = [
    {
        "source": "include/SportsPack.pch",
        "output": "SportsPack.mch",
        "mw_version": "Wii/1.3",
        "cflags": ["-lang=c++", *cflags_rp],
    },
]
config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "runtime",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "progress_category": "sdk",  # str | List[str]
        "objects": [
            Object(NonMatching, "runtime/global_destructor_chain.c"),
            Object(NonMatching, "runtime/__init_cpp_exceptions.cpp"),
        ],
    },
    {
        "lib": "RVL_SDK",
        "mw_version": "Wii/1.0",
        "cflags": cflags_rvl,
        "progress_category": "sdk",
        "objects": [
            # BTE: prebuilt older library, byte-identical to Wii Sports' (GC/3.0a5)
            Object(Matching, "revolution/BTE/stack/hcic/hcicmds.c", mw_version="GC/3.0a5"),
        ],
    },
    {
        "lib": "RP",
        "mw_version": "Wii/1.3",
        "cflags": cflags_rp_pch,
        "progress_category": "game",
        "objects": [
            Object(Matching, "Pack/RPGraphics/RPGrpDrawPathShadowTexture.cpp"),
            Object(Matching, "Pack/RPGraphics/RPGrpViewRender2D.cpp"),
            Object(Matching, "Pack/RPKernel/RPSysSystem.cpp"),
            Object(Matching, "Pack/RPSystem/RPSysSceneMgr.cpp"),
            Object(Matching, "Pack/RPSystem/RPSysGameConfig.cpp"),
            Object(Matching, "Pack/RPSystem/RPSysTagParms.cpp"),
            Object(NonMatching, "Pack/RPSystem/RPSysResourceManager.cpp"),
            Object(NonMatching, "Pack/RPSystem/RPSysSaveDataMgr.cpp"),
            Object(Matching, "Pack/RPKernel/RPSysTextWriter.cpp"),
            Object(NonMatching, "Pack/RPKernel/RPSysEffectMgr.cpp"),
            Object(Matching, "Pack/RPKernel/RPSysEffectBase.cpp"),
            Object(NonMatching, "Pack/RPKernel/RPSysEffectCreator.cpp"),
            Object(NonMatching, "Pack/RPKernel/RPSysHomeMenuMgr.cpp"),
            Object(NonMatching, "Pack/RPKernel/RPSysKokeshiUnk3C.cpp"),
            Object(Matching, "Pack/RPKernel/RPSysKokeshiManager.cpp"),
            Object(Matching, "Pack/RPGraphics/RPGrpCamera.cpp"),
            Object(Matching, "Pack/RPGraphics/RPGrpDrawPathManager.cpp"),
            Object(NonMatching, "Pack/RPGraphics/RPGrpModelAnmImplement.cpp"),
            Object(NonMatching, "Pack/RPGraphics/RPGrpModelImplement.cpp"),
            Object(NonMatching, "Pack/RPGraphics/RPGrpRenderer.cpp"),
            Object(Matching, "Pack/RPGraphics/RPGrpView.cpp"),
            Object(Matching, "Pack/RPGraphics/RPGrpViewRender3D.cpp"),
            Object(Matching, "Pack/RPGraphics/RPGrpDrawPathLightMap.cpp"),
            Object(Matching, "Pack/RPGraphics/RPGrpModelBoundingInfo.cpp"),
            Object(Matching, "Pack/RPGraphics/RPGrpShadowTexture.cpp"),
            Object(Matching, "Pack/RPGraphics/RPGrpCaptureTexture.cpp"),
            Object(NonMatching, "Pack/RPGraphics/RPGrpLightManager.cpp"),
            Object(NonMatching, "Pack/RPGraphics/RPGrpModel.cpp"),
            Object(NonMatching, "Pack/RPGraphics/RPGrpModelAnm.cpp"),
            Object(NonMatching, "Pack/RPGraphics/RPGrpModelManager.cpp"),
            Object(NonMatching, "Pack/RPGraphics/RPGrpModelResManager.cpp"),
            Object(NonMatching, "Pack/RPGraphics/RPGrpScreen.cpp"),
            Object(NonMatching, "Pack/RPGraphics/RPGrpModelScene.cpp"),
            Object(NonMatching, "Pack/RPGraphics/RPGrpModelMaterial.cpp"),
            Object(NonMatching, "Pack/RPGraphics/RPGrpModelRecord.cpp"),
            Object(NonMatching, "Pack/RPGraphics/RPGrpTexture.cpp"),
            Object(NonMatching, "Pack/RPGraphics/RPGrpFogManager.cpp"),
            Object(NonMatching, "Pack/RPGraphics/RPGrpProjectionObject.cpp"),
            Object(NonMatching, "Pack/RPGraphics/RPGrpModelRfl.cpp"),
            Object(NonMatching, "Pack/RPSystem/RPSysProjectLocal.cpp"),
            Object(NonMatching, "Pack/RPSystem/RPSysSceneCreator.cpp"),
            Object(Matching, "Pack/RPSystem/RPSysScene.cpp"),
            Object(NonMatching, "Pack/RPSystem/RPSysRenderMode.cpp"),
            Object(NonMatching, "Pack/RPSystem/RPSysLoadScene.cpp"),
            Object(NonMatching, "Pack/RPSystem/RPSysFontManager.cpp"),
            Object(Matching, "Pack/RPKernel/IRPSysHostIOSocket.cpp"),
            Object(NonMatching, "Pack/RPKernel/RPSysHostIOSocketManager.cpp"),
            Object(NonMatching, "Pack/RPKernel/RPSysFile.cpp"),
            Object(NonMatching, "Pack/RPKernel/RPSysController.cpp"),
            Object(NonMatching, "Pack/RPKernel/RPSysControllerMgr.cpp"),
            Object(Matching, "Pack/RPKernel/RPSysParticleManager.cpp"),
            Object(NonMatching, "Pack/RPAudio/RPSndHomeMenuArcMgr.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_8031641C.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_80319C98.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_80348158.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBowTrajectoryGuide.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBowBackgroundNpcManager.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_8034E974.cpp"),
            Object(Matching, "Pack/RPSports/RPBowScene/RPBow_8033FD0C.cpp"),
            Object(Matching, "Pack/RPSports/RPBowScene/RPBowActiveBall.cpp"),
            Object(Matching, "Pack/RPSports/RPBowScene/RPBowBallReturnRack.cpp"),
            Object(Matching, "Pack/RPSports/RPBowScene/RPBow_80347D0C.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBowMotionBlur.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_8034C95C.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBowNpcManager.cpp"),
            Object(Matching, "Pack/RPSports/RPBowScene/RPBowManagerContext.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_80332D14.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_8034656C.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBowPlayerLaneNpc.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_8031EFE4.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_80323790.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_803547A4.cpp"),
            Object(Matching, "Pack/RPSports/RPBowScene/RPBowGlobalLaneManager.cpp"),
            Object(Matching, "Pack/RPSports/RPBowScene/RPBow_80330EBC.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_8033B690.cpp"),
            Object(Matching, "Pack/RPSports/RPBowScene/RPBow_80329350.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_80329658.cpp"),
            Object(Matching, "Pack/RPSports/RPBowScene/RPBowPinSetter.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBowSwing.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_80320EFC.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_80327F0C.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_803381DC.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_8032F514.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_8032ADD8.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_804F7864.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_804F8590.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_804F89B8.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_804F8CD8.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_804F9054.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_804F93D0.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_804F974C.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_804F9848.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_804F9944.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_804F9B1C.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBowObstacleManager.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_804FAB54.cpp"),
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_804FADAC.cpp"),
            # Basketball 0x804FB3B8-0x8051B8B4: Bowling file found at the start of the range
            Object(NonMatching, "Pack/RPSports/RPBowScene/RPBow_804FB3B8.cpp"),
        ],
    },
    {
        "lib": "Sports2",
        "mw_version": "Wii/1.3",
        "cflags": cflags_rp_pch,
        "progress_category": "game",
        "objects": [
            # Basketball 0x8051B8B4-0x805479BC
            Object(NonMatching, "Sports2/Bsk/Bsk_8051B8B4.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8051C92C.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8051E9C0.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80520E80.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8052450C.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80524D2C.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80525BF4.cpp"),
            Object(NonMatching, "Sports2/Bsk/Config.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80526FC0.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80527F90.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8052876C.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80529D10.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8052A2B0.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8052AB40.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8052B120.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8052B34C.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8052F2A4.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80531A10.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80531C40.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80531ED8.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8053313C.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80534744.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80534CCC.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80535268.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80535700.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80535D2C.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80536910.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_805371E4.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_805374E0.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80538080.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80539324.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80539ED8.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8053AB50.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8053B084.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8053B1E8.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8053CD88.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8053D5BC.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8053D760.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8053FD00.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8053FF8C.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80542EA8.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_805433C0.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80547010.cpp"),
            Object(NonMatching, "Sports2/Arc/Arc_805479BC.cpp"),
            Object(NonMatching, "Sports2/Arc/Analyzer.cpp"),
            Object(NonMatching, "Sports2/Arc/Arc_80549568.cpp"),
            Object(NonMatching, "Sports2/Arc/Camera.cpp"),
            Object(NonMatching, "Sports2/Arc/Field.cpp"),
            Object(NonMatching, "Sports2/Arc/TargetMgr.cpp"),
            Object(NonMatching, "Sports2/Arc/AvatarMgr.cpp"),
            Object(NonMatching, "Sports2/Arc/SequenceMgr.cpp"),
            Object(NonMatching, "Sports2/Arc/ObjMgr.cpp"),
            Object(NonMatching, "Sports2/Arc/Wipe.cpp"),
            Object(NonMatching, "Sports2/Arc/Arc_80571BC8.cpp"),
            Object(NonMatching, "Sports2/Arc/SignMgr.cpp"),
            Object(NonMatching, "Sports2/Arc/EffectMgr.cpp"),
            Object(NonMatching, "Sports2/Arc/Arc_8057750C.cpp"),
            Object(NonMatching, "Sports2/Arc/Arc_80577838.cpp"),
            Object(NonMatching, "Sports2/Arc/Arc_80578790.cpp"),
            Object(NonMatching, "Sports2/Arc/ObstacleMgr.cpp"),
            Object(NonMatching, "Sports2/Arc/Arc_8057AC9C.cpp"),
            Object(NonMatching, "Sports2/Arc/Arc_8057B014.cpp"),
            Object(NonMatching, "Sports2/Arc/Arc_8057BC08.cpp"),
            Object(NonMatching, "Sports2/Arc/Arc_8057C020.cpp"),
            Object(NonMatching, "Sports2/Arc/Arc_8057C4CC.cpp"),
            Object(NonMatching, "Sports2/Arc/Arc_8057C790.cpp"),
            Object(NonMatching, "Sports2/Arc/BonusTargetMgr.cpp"),
            Object(NonMatching, "Sports2/Arc/Arc_8057DE9C.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_8057E310.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_8057FC50.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_80583C50.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_80586434.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_80587A3C.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_80588A6C.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_80589050.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_8058ACDC.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_8058BE50.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_8058D034.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_8058DBD4.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_8058F908.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_805904CC.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_80594890.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_805965A4.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_80597C94.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_80598140.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_805982C0.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_80598F80.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_80599070.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_805991CC.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_805995D8.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_80599B9C.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_80599DEC.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_80599F68.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_8059A320.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_8059D994.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_8059EA38.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_805A0AFC.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_805A0C7C.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_805A2A20.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_805A4334.cpp"),
            Object(NonMatching, "Sports2/Wkb/Wkb_805A568C.cpp"),
            Object(NonMatching, "Sports2/Wkb/Wkb_805A673C.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_805A6958.cpp"),
            Object(NonMatching, "Sports2/Wkb/Wkb_805A6D28.cpp"),
            Object(NonMatching, "Sports2/Wkb/Wkb_805A8C64.cpp"),
            Object(NonMatching, "Sports2/Wkb/Wkb_805A9730.cpp"),
            Object(NonMatching, "Sports2/Wkb/Wkb_805A9F08.cpp"),
            Object(NonMatching, "Sports2/Wkb/Wkb_805AA6F8.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_805AB8E0.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_805AC45C.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_805AC80C.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_805ACC08.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_805AD7DC.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_805AE610.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_805AE904.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_805AEB80.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_805AFFB8.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_805B0720.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_805B1DF8.cpp"),
            Object(NonMatching, "Sports2/Wkb/Wkb_805B2D7C.cpp"),
            Object(NonMatching, "Sports2/Wkb/Wkb_805B3070.cpp"),
            Object(NonMatching, "Sports2/Wkb/Wkb_805B32F4.cpp"),
            Object(NonMatching, "Sports2/Wkb/Wkb_805B3480.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_805B3870.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_805B3AF4.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_805B404C.cpp"),
            Object(NonMatching, "Sports2/JskWkb/JskWkb_805B4820.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_805B53C8.cpp"),
            Object(NonMatching, "Sports2/Jsk/Jsk_805B5AE0.cpp"),
            # Basketball 0x804FB3B8-0x8051B8B4
            Object(NonMatching, "Sports2/Bsk/Scene.cpp"),
            Object(NonMatching, "Sports2/Bsk/GraphManager.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_804FCA30.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_804FF124.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_804FF434.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80500C40.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80503928.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80504C9C.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80508C6C.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8050A7D8.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8050C224.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80510EBC.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80511554.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8051185C.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8051224C.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80512944.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_805150D4.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_805153E0.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80516A4C.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80516B18.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_805178A4.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_80519260.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8051A5C4.cpp"),
            Object(NonMatching, "Sports2/Bsk/Bsk_8051AA48.cpp"),
            # Frisbee Dog 0x805B5FD8-0x805EFD7C (namespace Sp2::Fld::Ddg)
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805B5FD8.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805B65E0.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805B7968.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805BA6C0.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805BD21C.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Scene.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805C29FC.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805C3AA8.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805C7090.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805C7348.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805CA164.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805CAE14.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805CBDF0.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805CCE88.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805CDABC.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805CDF14.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805CEE7C.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805CFBAC.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805D2944.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805D483C.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805D51B8.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805D89E8.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805DADC0.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805DC06C.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805DF4D0.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805E48DC.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805E5264.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805E60CC.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805E61A0.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805E6F5C.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805E9B70.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805EA20C.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805EB33C.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805EC01C.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805EC330.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/RingMgr.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805EF944.cpp"),
            Object(NonMatching, "Sports2/Fld/Ddg/Ddg_805EFC74.cpp"),
            # Canoeing 0x80489030-0x804C17A8
            Object(NonMatching, "Sports2/Can/Can_80489030.cpp"),
            Object(NonMatching, "Sports2/Can/Can_80489D84.cpp"),
            Object(NonMatching, "Sports2/Can/Config.cpp"),
            Object(NonMatching, "Sports2/Can/Can_8048BF10.cpp"),
            Object(NonMatching, "Sports2/Can/Can_80494264.cpp"),
            Object(NonMatching, "Sports2/Can/Can_80494884.cpp"),
            Object(NonMatching, "Sports2/Can/Can_8049580C.cpp"),
            Object(NonMatching, "Sports2/Can/Can_80495CD8.cpp"),
            Object(NonMatching, "Sports2/Can/Can_80496010.cpp"),
            Object(NonMatching, "Sports2/Can/Can_80497B80.cpp"),
            Object(NonMatching, "Sports2/Can/Can_80497D94.cpp"),
            Object(NonMatching, "Sports2/Can/Can_80498BEC.cpp"),
            Object(NonMatching, "Sports2/Can/PlayerMgr.cpp"),
            Object(NonMatching, "Sports2/Can/Can_80499F7C.cpp"),
            Object(NonMatching, "Sports2/Can/Can_8049A1BC.cpp"),
            Object(NonMatching, "Sports2/Can/FieldMgr.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804A3BC0.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804A3DD8.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804A4500.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804A4B08.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804A5880.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804A6C88.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804A7AD4.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804A7C68.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804A8754.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804A95B8.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804A9868.cpp"),
            Object(NonMatching, "Sports2/Can/SequenceMgr.cpp"),
            Object(NonMatching, "Sports2/Can/Main.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804B171C.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804B6D58.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804B727C.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804B7530.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804B888C.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804B8A00.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804B8B08.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804B8C70.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804B9448.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804B9D44.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804BAA34.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804BAFE0.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804BB2AC.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804BB5F4.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804BB85C.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804BC530.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804BD6BC.cpp"),
            Object(NonMatching, "Sports2/Can/Can_804BE8B8.cpp"),
            Object(NonMatching, "Sports2/Can/VSMgr.cpp"),
            # Swordplay lane 1 0x805EFD7C-0x806108AC
            Object(NonMatching, "Sports2/Swf/Swf_805EFD7C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_805F0C58.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_805F181C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_805F1B0C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_805F1F8C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_805F21CC.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_805F547C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_805FAEB0.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_805FB19C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_805FD574.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_805FF240.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80600BA8.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80602BD4.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80604314.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80604CE0.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80607E84.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_806087E4.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8060A160.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8060A6E0.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8060AAB4.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8060B168.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8060B71C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8060C060.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8060C1E4.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8060C73C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8060CB6C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8060E6E4.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8060FC28.cpp"),
            # Swordplay lane 2 0x806108AC-0x8062E938
            Object(NonMatching, "Sports2/Swf/Swf_806108AC.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80611D44.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8061204C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_806121F0.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_806122E4.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_806124AC.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80612650.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80612A24.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80614864.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80615154.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80615BEC.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8061F194.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80621738.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80624988.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80624C50.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80625D00.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80627ED0.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80629B98.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8062AA6C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8062B23C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8062BB8C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8062C234.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8062CB80.cpp"),
            # Swordplay lane 3 0x8062E938-0x80653FA0 (end of .text)
            Object(NonMatching, "Sports2/Swf/Swf_8062E938.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80630330.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8063269C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8063348C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80633C38.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80635720.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80636E9C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80638D40.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_806394F8.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8063A0C4.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8063BD58.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8063F630.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_806419C4.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80642EB8.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80643A54.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80643B54.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80643ED4.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_806440D4.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_806443F0.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_806447D8.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_806451C0.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80645564.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_806457E0.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_806464DC.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8064BC30.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8064C09C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8064CC58.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8064CF28.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8064E0EC.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8064E330.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8064E568.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8064E7B4.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8064F064.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8064F2B0.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80650440.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8065137C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80651A64.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80651DBC.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80652004.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_80652274.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8065235C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_8065277C.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_806530E4.cpp"),
            Object(NonMatching, "Sports2/Swf/Swf_806535A0.cpp"),
        ],
    },
    {
        # Resort shared state machine base (template: include/Sports2/Unk_StateMachine.h)
        "lib": "Sports2Cmn",
        "mw_version": "Wii/1.3",
        "cflags": cflags_rp_pch,
        "progress_category": "game",
        "objects": [
            Object(NonMatching, "Sports2/Unk_803456D0.cpp"),
        ],
    },
]


# Objects ported from ogws by tools/port_flip.py (per-object compiler and flags).
import json as _json
_ported_path = Path("config") / config.version / "ported_objects.json"
config.reconfig_deps = [*(config.reconfig_deps or []), _ported_path]
if _ported_path.exists():
    config.libs.append({
        "lib": "ported",
        "mw_version": config.linker_version,
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, p["name"], mw_version=p["mw_version"], cflags=p["cflags"])
            for p in _ported_json if True
        ] if (_ported_json := _json.load(open(_ported_path))) is not None else [],
    })


# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: List[str]) -> List[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects


# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback


# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("game", "Game Code"),
    ProgressCategory("sdk", "SDK Code"),
]
config.progress_each_module = args.verbose
# Optional extra arguments to `objdiff-cli report generate`
config.progress_report_args = [
    # Marks relocations as mismatching if the target value is different
    # Default is "functionRelocDiffs=none", which is most lenient
    # "--config functionRelocDiffs=data_value",
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
