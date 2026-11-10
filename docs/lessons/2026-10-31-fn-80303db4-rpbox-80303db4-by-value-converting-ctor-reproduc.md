# fn_80303DB4 (RPBox_80303db4): by-value converting ctor reproduces target stack slot/store order; remaining FPR colour + post-RA schedule wall (96.9)

- status: fails
- tags: rpbox,80303db4,fpr,stack-slot,by-value,lerp
- source: worker flip-b3db 2026-10-31

symptom: 96.9%: target stack is copy+local per vector (a-copy 0x14, a 0x74, b-copy 0x08, b 0x68; stored copy,local,copy,local); head lerps and u/v2 LerpR block differ ~20 lines each by FPR colouring then scheduling
cause: two parts: slot/store order (reproducible with BoxVec3(BoxVec3 v,int) taking source by value, invented ctor so R17) and FPR colouring (unk74 results f30/f31, unk68.x f29) plus post-RA scheduling
fix: Dead: first/second decl swap, lerp call order (96.0/95.8), return-by-value/copy-init/explicit temps (elided, 90-92), nested by-value LerpVector (91.7), one Blend inline with 2 by-value params (95.9), 5x5 lerp helper forms x 2 call orders on ctor base (max 96.9), all-temps-then-store (95.4). MWCC inline 2 by-value params: leftmost param = higher slot, stores right-to-left. Hand FPR map: a.xyz=f11/f10/f9, b.xyz=f8/f7/f6, rate f28, 1-t f5. Next: feed hand map to fpr_replay.py search from the ctor structure; else park.
