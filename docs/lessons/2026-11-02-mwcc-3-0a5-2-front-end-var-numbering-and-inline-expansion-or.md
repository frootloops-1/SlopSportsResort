# MWCC 3.0a5.2 front-end var numbering and inline expansion order

- status: works
- tags: colouring,mwcc_dbg,IRO,inline,CSE,numbering
- source: golfield-fn-1102

symptom: need to predict which vreg is coloured first
cause: colouring is pure descending vreg (Coloring.c simplify: ascending sweep, push if degree<29). Numbering: named locals lowest (first declared highest), then @N inline/IRO vars in reverse @N order (later-created = lower), then codegen temps in codegen order. Nested inline calls are expanded after all top-level ones in the function (higher @N). IRO CSE vars are created in source order of first occurrence. A copy of a global (p = global) is copy-propagated, then CSE recreates it as @N
fix: use these rules with tools/mwcc_dbg.sh (12 s per run) and mwcc_frontend_trace.py --frontend-limit 200 (stage list incl. RebuildLogicalExpressions) before trying spellings
