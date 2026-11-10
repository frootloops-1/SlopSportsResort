# RPUtlMapData fn_801BF6C4: 10 min permuter, 9.6k iterations, nothing beats base 40

- status: fails
- tags: permuter,register,mapdata
- scope: src/Pack/RPUtility/RPUtlMapData.cpp

symptom: base score 40 (7 lines), no candidate lower in 9652 iterations with PERMUTER_DIR=~/Downloads/decomp-permuter and --name fn_801BF6C4 --static
cause: register residue not reachable by permuter mutations of this body
fix: No fix; parked. Earlier run was also valid (compile.sh splices into real source).
