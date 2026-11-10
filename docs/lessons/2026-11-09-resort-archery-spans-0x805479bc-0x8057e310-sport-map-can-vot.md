# resort: Archery spans 0x805479BC-0x8057E310 (sport_map 'can' votes on sinit_80576C7C wrong)

- status: works
- tags: resort,sport-map,archery
- scope: resort
- source: archery

symptom: sport_map understates Archery
cause: scene file hides at the end of sinit_80547010 (Basketball); Archery ends inside sinit_80576C7C, rest is jsk/wkb
fix: Archery = Sports2/Arc/ 25 units; 0x80547010-0x805479BC is Basketball (unk/text_80547010); 0x8057E310+ is Power Cruising/Wakeboarding (unk/sinit_8057E310)
