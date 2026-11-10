# REGSEARCH_DIFF=1 ranks by asm_diff lines; DrawPathDOF Lite/Standard residue survives 2687-order exhaustive search and helper shapes

- status: fails
- tags: drawpathdof,regsearch,metric,scheduler
- scope: egg/gfxe/eggDrawPathDOF

symptom: Lite 26 diff lines, Standard 4 after the first round of levers
cause: the default regsearch score ignores float colour/schedule-only diffs, so its winners were worse by asm_diff; with the aligned metric every statement order of the loop block (2687), 25 generic sites, access forms and inline-helper wraps give >= 26
fix: no source change this round. Tool: REGSEARCH_DIFF=1 (tools/regsearch.py) makes lines/score equal asm_diff's count (Lite 26 verified). Next lever must change the pcode DAG (e.g. which inline owns the size loads), not statement order
