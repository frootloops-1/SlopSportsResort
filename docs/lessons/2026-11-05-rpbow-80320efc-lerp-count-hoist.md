# RPBow_80320EFC lerp count hoist

- status: works
- tags: rpbow,fpr,inline

symptom: inlined table lerp reloads count and recomputes n-1 per loop iteration
cause: original held n in a local across the loop
fix: helper takes n as param, caller loads int n before loop and reuses it for later call; size back to 4112; then regsearch decl hoists 98.0->98.2
