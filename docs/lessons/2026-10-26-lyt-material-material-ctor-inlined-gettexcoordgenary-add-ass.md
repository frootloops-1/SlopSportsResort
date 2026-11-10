# lyt_material Material ctor: inlined GetTexCoordGenAry add association (base+srt)+map vs base+(srt+map)

- status: fails
- tags: lyt_material,nw4r,ctor,inline,cse,add-order
- scope: nw4r/lyt/lyt_material
- source: session 2026-10-26

symptom: Material::Material 99.99%: 10-line diff, ours add(srt*0x14,map*0x1c) then +mpGXMem; retail adds mpGXMem+srt first then +map. Standalone GetTexCoordGenAry already emits retail order.
cause: CW reassociates base+(A+B) to (base+A)+B only when the sum is not shared; in the ctor the first site (hoisted before SetTexCoordGenNum's if) keeps A+B grouped. Unknown source form that avoids it.
fix: Dead ends: swap Calc operand order (commutative no-op), const ptr, int/u8/u32 loop, SetTexCoordGenNum before Get (reassociates but loses hoist, 84 lines), pointer above pTexSrt, direct ConvertOffsToPtr call, pTexSrt+texSRT form, dropping const in SetTexCoordGenNum.
