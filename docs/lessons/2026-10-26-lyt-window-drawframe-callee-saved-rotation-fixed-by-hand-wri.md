# lyt_window DrawFrame callee-saved rotation fixed by hand-written LT texcoord block (marker)

- status: works
- tags: regalloc,callee-saved,rotation,inline,lyt,marker,forecast
- scope: nw4r/lyt/lyt_window
- source: worker opus2 2026-10-26

symptom: Window::DrawFrame 98.2: identical instruction stream, all callee-saved regs rotated by one (flipInfos static-table base r31 vs retail r21) plus volatile renumbering in the first block
cause: Retail keeps coords[LT][ix]/[iy] (and texSize w/h) in named locals in the first (LT) block; via the GetLTTexCoord inline they are CSE temps, which changes colouring order. Helper-level locals break DrawFrame4/8 (93%)
fix: Write the LT block out in DrawFrame (u8 ltx,lty; int iy,ix declared up front; f32 th,tw; VEC2 tsize(tw,th)) as the Forecast Channel decomp does -> 100.0. MATCH-PENDING R17: @-label numbering shifts -7 vs retail (cosmetic; @6777 size 4!=8 in unit_cmp). Check other decomps (~/Downloads/forecast-main, Petari-master) for an already-matched shape before deriving levers
