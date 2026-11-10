# Non-const static reloaded per component

- status: works
- tags: rpbox,static,lfs
- source: RPBox_802cf93c

symptom: target reloads a static (VEC3_ZERO) and interleaves lfs/stfs
cause: const static folded into one load
fix: declare the static non-const (67.4->89.4 in fn_802D485C)
