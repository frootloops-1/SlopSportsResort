# Negated conjunction beats swapped branches: !(a != X && b != Y) { A } else { B }

- status: works
- tags: permuter,branch,ppc
- scope: Pack/RPAudio

symptom: setOutputMode 99.76%: if (p != A && p != B) {DPL2} else {STEREO} gives different branch shape
cause: MWCC lowers a negated && differently from the swapped-body form and from ==/|| form (|| form regressed to 22 diff lines)
fix: if (!(p != A && p != B)) { STEREO } else { DPL2 }; found by tools/permute.py in 1 minute (perm_ negate/swap)
