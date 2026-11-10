# fn_801C3574: inline boundaries around w/h/ratio/half-extent do not change the schedule

- status: fails
- tags: schedule,inline,fpr,frustum,wall
- scope: Pack/RPUtility/RPUtlLytBase/fn_801C3574
- source: claude-sonnet

symptom: Hoped an EGG-style inline helper (aspect wrapper, calcAspect(u16,u16)/(f32,f32), halfWidth(y,aspect), halfExtents(near,tan,w,h), Frustum-style GetNearZ/GetTanFovy accessors) would reorder the prologue schedule
cause: Inlining is resolved before scheduling, so the post-inline DAG is identical: all 9 variants keep our order (stw_a0 frsp lfs14 lfd_a0 fmuls1), scores 38..48 vs 38 base. Context: ProjectionState is the EGG::Frustum layout (0x14 mTanFovY, 0x18 mNearZ), y = nearZ*tanFovy, aspect from Screen::GetSizeXMax/YMax tables.
fix: none: only changes to the instruction DAG itself (extra consumer of the product chain, different consumer of fdivs) can move it; helper boundaries cannot
