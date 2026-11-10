# resort: Bowling layout shifts show as every offset moved by a constant; insert pads

- status: works
- tags: resort,bowling,layout
- scope: resort
- source: bowling-lanes

symptom: same loads/stores, offsets all +4/+8/+0x1C vs ogws (NpcContext, BowLane, BowCam, NpcModelGroup)
cause: Resort added members to ogws Bowling structs
fix: insert pads at the first shifted offset and re-diff; NpcContext 88 -> 100 on several functions. Where Resort rewrote a class (BowCamera, BowSwing) add a separate Resort view instead of bending the ogws struct
