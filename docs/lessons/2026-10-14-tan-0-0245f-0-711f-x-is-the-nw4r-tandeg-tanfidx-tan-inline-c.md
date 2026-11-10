# tan(0.0245f*(0.711f*x)) is the nw4r TanDeg -> TanFIdx -> tan inline chain

- status: works
- tags: tan,nw4r,math,inline,float
- scope: RPTns_8023ef24
- source: opus worker 2026-10-14

symptom: const registers wrong and .sdata2 order needs a hoist
cause: inlined TanDeg(deg) = TanFIdx(deg*256/360), TanFIdx(f)=tan(f*PI/128)
fix: use the inline chain (local copies or nw4r::math); load a member used after the call into its own local (fn_8023EF24)
