# DrawPathDOF Standard: far-before-near fog loads need far earlier in pcode; direct GXSetFog args cannot give it

- status: fails
- tags: drawpathdof,scheduler,call-args,inline
- scope: egg/gfxe/eggDrawPathDOF

symptom: internalDrawStandard 4 lines: target lfs far(0x1c) before fnmsubs and near(0x18) after it, both after the fog colour stb copy
cause: call codegen: inline-getter args are pre-evaluated right-to-left BEFORE the by-value GXColor copy (loads then cannot pass the byte stores), plain args are loaded left-to-right after it; so far-before-near-after-copy is unreachable with a direct GXSetFog call
fix: failed: getters (8), far/near locals (4/8), const fogColor (8), static_cast<const GXColor&> (8), GXColor& alias (8), mixed getter/raw (6/8). Untested: an inline wrapper whose param binding order puts far first after the copy
