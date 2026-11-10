# resort: RPGrpModel/RPGrpModelAnm flag clears are bitfields (rlwinm), and RPGrpModelAnm base is 0x7C with Start at slot 0x68

- status: works
- tags: resort,rpgrpmodel,bitfield,vtable

symptom: u16 &= ~mask gives andi.
cause: Flags are bitfields in a union
fix: union {u16 mFlags; struct {bitfields}}; RPGrpModelAnm still needs its real 8 x 0xC entry layout (0x10 pad placeholder now)
