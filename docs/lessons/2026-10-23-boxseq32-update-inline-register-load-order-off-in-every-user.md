# BoxSeq32::Update inline register/load order off in every user

- status: open
- tags: rpbox,inline,regalloc
- source: RPBox_802cf93c 2026-10-23

symptom: target next in r4/cur in r0, loads cur before prev in cur!=prev, and reloads cur twice (switch value + prev=cur); ours swaps regs and loads once
cause: Update inline shape differs from original (fields/locals/order unknown); hits fn_802CF94C, fn_802D3CF8, fn_802D6230
fix: untried: fixing the shared inline could lift all three
