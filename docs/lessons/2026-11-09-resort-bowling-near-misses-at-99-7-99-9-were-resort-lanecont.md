# resort: Bowling near-misses at 99.7-99.9 were Resort LaneContext/PinPhysicsBody offsets

- status: works
- tags: resort,bowling,RPBow,layout
- scope: resort
- source: RP batch 4 (2026-11-09)

symptom: ogws-ported RPBowPinSetter functions miss by one load offset each
cause: Resort LaneContext pinCount 0x18, throwContext 0x2BEC, setterAnm 0x2D30; PinPhysicsBody +0x1C
fix: diff load offsets first; fix bowling.h; both RPBow units Matching after also extending their splits to vtable/pool/sinit ranges
