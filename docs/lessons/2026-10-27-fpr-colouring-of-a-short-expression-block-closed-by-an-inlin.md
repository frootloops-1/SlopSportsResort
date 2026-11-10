# FPR colouring of a short expression block closed by an inline helper with (screen, radius, z) params

- status: works
- tags: fpr,inline,helper,register
- scope: RPUtlDohGraphSun
- source: claude/rputl-doh-1027

symptom: same 10 instructions, recip/radius/z in f2/f3/f4 rotated vs retail f4/f2/f3
cause: inline parameter copies are coloured before body temps; local decl order and operand order alone could not reach it (~40 forms)
fix: static inline screenRadius(const Screen*, f32 radius, f32 z) using EGG::Mathf::inv and nw4r::math::FAbs; marker row 26
