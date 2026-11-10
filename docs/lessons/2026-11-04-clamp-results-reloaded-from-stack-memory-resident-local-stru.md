# Clamp results reloaded from stack = memory-resident local struct filled by a loop (b340 BD58)

- status: works
- tags: stack-struct,loop,lerp,vec3,b340
- scope: RPSportsCommon/RPSports_8020b340
- source: claude/b340-1104d 376789b97

symptom: retail stores clamp results per branch and reloads from stack; ours keeps in regs
cause: Original used a local struct filled by a short loop; VEC3 ctor args evaluate right-to-left
fix: SelClampArgs r filled by 3-iteration loop; inline selLerpAll->selLerpV returning VEC3(x,y,z) with named x,y for x-first evaluation. BD58 70.6->89.2, DED4 54.8->57.9
