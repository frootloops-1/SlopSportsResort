# lyt_window DrawFrame: helper/decl/arg-shape variants do not move the flipInfos-base rotation

- status: fails
- tags: regalloc,callee-saved,rotation,lyt,dead-end
- scope: nw4r/lyt/lyt_window
- source: worker opus2 2026-10-26

symptom: flipInfos base r31 vs retail r21 in Window::DrawFrame
cause: Colouring is driven by the LT inline expansion's CSE temps, not by these spellings
fix: No change (stays 98.2): inline/int param on GetTexutreFlipInfo, pointer rInfo, int/u8/u32/const ix/iy, texSize VEC2 first, VEC2[] param, Petari add order, Petari DrawFrame body (const bool/const Size/texCoordNum), braces per corner, decl order of vtxColors/texCoords/point/size, *texCoords/&texCoords[0][0] args. Moving vtxColors after the LT call regresses to 83.8
