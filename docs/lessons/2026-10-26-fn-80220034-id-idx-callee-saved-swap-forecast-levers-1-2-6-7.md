# fn_80220034 id/idx callee-saved swap: forecast levers 1/2/6/7 flat (parked 99.8)

- status: fails
- tags: forecast,regalloc,callee-saved,declaration-order,parked
- scope: RPTns_8021ba24/fn_80220034
- source: forecast-regalloc

symptom: target idx r31, flag r30, self r29, id r28; ours id r31 ... idx r28 (10 lines)
cause: local id (ConvertLabelStringToSoundId result) always coloured before the params; only two outcomes reachable: id r31 + params reversed (99.2) or current (99.8 with u32* pidx=&idx)
fix: dead ends: id declared up front (u3,y1-y4), unsigned int/s32 id, u32& rid=id, u32* pid=&id (sibling fn_8021FC14 style + Tns* static helpers), pidx placement, pflag, inline helper for shared body, early-return shape
