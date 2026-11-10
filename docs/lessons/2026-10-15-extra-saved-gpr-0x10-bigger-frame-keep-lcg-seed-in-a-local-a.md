# Extra saved GPR / 0x10 bigger frame: keep LCG seed in a local across two random draws (ef_disc idiom)

- status: works
- tags: nw4r,ef,emform,random,frame
- scope: nw4r/ef

symptom: ef_cylinder EmissionSub 99.27%, frame 0x1d0 vs 0x1c0, savegpr_19 vs _20
cause: orig holds seed in r19 across both draws; two RandFloat() calls reload mRandom
fix: u32 rs = reinterpret_cast<u32&>(mRandom) = ...*0x343FD+0x269EC3; SeedToFloat(rs); second draw rs = mRandom = rs*0x343FD+0x269EC3
