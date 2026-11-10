# Controller trigger test as mask & trig needs a view, not downTrigger

- status: works
- tags: egg,controller,operand-order
- scope: Pack/RPSports/RPTnsScene/RPTns_802338a4

symptom: and. r0,r0,r29 vs target and. r0,r29,r0 (mask first) after getNthController(i)
cause: CoreStatus::downTrigger is trig & buttons; mCoreStatus is protected
fix: provisional struct view {u8 pad[0x18]; u32 trig;} and write mask & view->trig
