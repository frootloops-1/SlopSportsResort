# ef_animcurve full match: reference pKey and reused value cursor close F32

- status: works
- tags: ef_animcurve,F32,forecast,key-layout,full-match
- scope: nw4r/ef/ef_animcurve
- source: User-supplied ef_animcurve.cpp (3011 lines); branch codex-animcurve-reference-20261102

symptom: Only F32 remained at 99.04905: 24 normalized instruction diff lines in lo initialization and interpolation key setup; all other functions exact.
cause: Moving interp before flags alone is insufficient. A separate pKey for interpolation plus a reused pValue with k0/k1 recovered from value addresses preserves the reference key/value structure and gives the exact scheduler/register palette. The reference uses an 8-byte key header with packed interp; Wii Sports needs 12 bytes and per-component interpolation bytes.
fix: Split found/lo declarations and assign lo=0 before found; pKey=keys+idx*keySize, pValue=(f32*)(pKey+12), v0=pValue, k0=(u8*)pValue-12, reuse pValue for the next key, v1=pValue, k1=(u8*)pValue-12, interp=pKey+4, then read flags/bools. Keep existing range-size R17 and GC/3.0a5.2. Verify 6/6 exact, .text/.sdata2 100, order0, flip_gate --keep FLIP-OK with DOL0 and only 3 known collisions. No new marker.
