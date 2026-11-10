# Saved-reg order for p140 bodies: hold &body->v68 not body

- status: works
- tags: regalloc,mwcc,psq
- source: RPBox_802cf93c 2026-10-23

symptom: two BoxBody140* locals got r29/r28 while &stack-vec temps got r31/r30 (99.2%)
cause: local pointer type/offset changes allocation priority
fix: BoxV3Pod* a = &x->p140->v68; pass a directly to PodSub/PodAdd (fn_802D5B3C 100)
