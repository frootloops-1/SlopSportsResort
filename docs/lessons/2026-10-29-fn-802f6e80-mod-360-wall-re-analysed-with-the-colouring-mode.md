# fn_802F6E80 mod-360 wall re-analysed with the colouring model: A needs an r0-coloured neighbour; no source lever found

- status: fails
- tags: RPBox_802f6be0,coloring,regalloc,scheduler
- scope: RPBox_802f6be0

symptom: target add r4/srawi r4/srwi r0; ours add r0/srawi r0/srwi r4 (99.77%)
cause: SelectColors is lowest-free-colour with no hints, so target A=r4 means A had a neighbour coloured r0 when coloured; ours A's only neighbour is n (r5). S=r4/U=r0 additionally needs U coloured before S, but U (r59) is numbered below S (r64) by instruction selection (division expansion), so S is coloured first and takes r0. Pre-RA Scheduler hoists the h00 lhz/ori/sth into the mulhw shadow (initial code has them after the chain), so they never overlap A. Scheduler memory deps are per object (member objects disambiguate h00/h02), so source order does not pin them. 8-min generic regsearch (140 evals) no gain.
fix: Parked again. Untried: a construct that makes A live across an r0 value (would need the h00 store after the chain pre-RA, but post-RA order must still put sth h00 before add); check Scheduler.c fn_004cd650 volatile-object path. New tool: tools/color_sim.py <mwcc_dbg dump> replays Coloring_SimplifyGraph (K=29) to show colour order / neighbours.
