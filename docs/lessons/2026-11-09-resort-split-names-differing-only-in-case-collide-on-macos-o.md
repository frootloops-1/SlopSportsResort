# resort: split names differing only in case collide on macOS (one object overwrites the other)

- status: works
- tags: resort,splits,macos,case,linker
- scope: splits.txt
- source: carve_unk.py --gaps 2026-11-09

symptom: Link error: undefined nw4r::snd::DvdSoundArchive::__vt referenced from an auto_ text object, after adding a split
cause: splits.txt had nw4r/snd/snd_dvdSoundArchive.cpp (mkw spelling) and the new nw4r/snd/snd_DvdSoundArchive.cpp; on a case-insensitive filesystem both build to one .o, so one unit's data vanished
fix: Compare unit names case-insensitively (port_splits.py, carve_unk.py) and map other projects' spellings to ogws in tools/unit_paths.py; merge the two pieces into one unit
