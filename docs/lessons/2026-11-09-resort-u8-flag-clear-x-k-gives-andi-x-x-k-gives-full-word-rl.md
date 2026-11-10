# resort: u8 flag clear 'x &= ~K' gives andi.; 'x = x & ~K' gives full-word rlwinm (28,26)

- status: works
- tags: resort,codegen,bitfield,flags
- source: rp-graphics-layouts worker 2026-11-09

symptom: retail rlwinm r0,r0,0,28,26 between lbz/stb, ours andi. r0,r0,0xef
cause: compound assignment on a u8 keeps byte width
fix: write the explicit assignment form (EGG::LightTextureManager::SetEnable)
