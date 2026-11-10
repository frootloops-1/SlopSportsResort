# fn_8024F7C0 (RPBsb_8024e9a4): 10-min permuter (-j2, keep-bodies) finds no state below base 30

- status: fails
- tags: rpbsb,permuter,fpr,fn_8024F7C0
- scope: RPBsb_8024e9a4

symptom: fadds f2 vs f1 (3 instrs) after 8 source-shape variants
cause: permuter frontier empty: no candidate beat base score 30 in 10 min; wall is a scheduler/RA tie not reachable by spelling
fix: none; do not rerun permuter. setup: PERMUTER_DIR=../decomp-permuter permute.py setup --name fn_8024F7C0 --keep-bodies <unit> fn_8024F7C0
