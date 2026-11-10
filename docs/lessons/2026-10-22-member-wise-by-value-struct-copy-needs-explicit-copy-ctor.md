# Member-wise by-value struct copy needs explicit copy ctor

- status: works
- tags: struct-copy,by-value
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc
- source: claude-rpbox-802cb9cc-1022

symptom: by-value record arg copied with lwzu/stwu loop instead of per-member lwz/lbz/lfs
cause: POD (even with user ctor) gets a block copy; original copies member-wise, nested 2-float struct as words
fix: inline copy ctor assigning members in order; copy nested float pair via int-pair cast
