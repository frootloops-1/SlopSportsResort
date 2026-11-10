# DrawStripeStrategy::Draw: declare drawOrder first, then option, then connect fixes lbz/lhz load order

- status: works
- tags: schedule,load-order,decl-order,nw4r,ef
- scope: ef_drawstripestrategy

symptom: 98.1%: target loads typeOption(0xa1), typeOption2(0xa6), flags(0x0) in that order; ours loaded 0xa1, flags, 0xa6
cause: Source order of the three bitfield-ish byte reads drives load scheduling and reg colouring
fix: int drawOrder = flags & MASK; int option = (typeOption==2?2:0)|(drawOrder?4:0); int connect = typeOption2 & 7;  (original order connect/drawOrder/option gave 98.1, option-first split gave 97.9)
