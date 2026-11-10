# resort library: ResAnm*Data has an extra word at 0x1C, info at 0x20

- status: works
- tags: resort,library,port

symptom: g3d resanm offsets off by 4
cause: Resort NW4R revision
fix: unk_1C in ResAnmChrData (confirmed), ResAnmVisData likely
