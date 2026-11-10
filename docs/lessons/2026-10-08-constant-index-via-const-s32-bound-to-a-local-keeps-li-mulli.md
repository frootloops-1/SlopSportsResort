# Constant index via const s32& bound to a local keeps li+mulli

- status: works
- tags: mulli,constant-index

symptom: orig 'li rX,N; mulli rY,rX,0x18' but ours folds offsets
cause: late constant propagation when index read through a reference to a local that is reassigned per block
fix: const s32& type = typeVal; typeVal=1 for next block (fn_801E2970 82.4->89.8; first access still folds)
