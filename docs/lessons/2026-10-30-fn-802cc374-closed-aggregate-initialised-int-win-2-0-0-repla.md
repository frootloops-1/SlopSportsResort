# fn_802CC374 closed: aggregate-initialised int win[2] = {0, 0} replaces opt_unroll_loops pragma + fake 1-trip loop

- status: works
- tags: unroll,loop,vreg,colour,scalarize,array
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc
- source: claude-op-cb9cc-20261031

symptom: 3-trip if/else loop fully unrolled by our build (ctr loop in target), and counter GPRs numbered below the hoisted constants (target colours hi,lo first)
cause: a brace-initialised local array is scalarised LATE: at full-unroll time the counters are still memory ops (body over the size limit, so no unroll), and the late scalar temps get the newest vregs (above codegen constants). Separate win[0]=0; win[1]=0; stores scalarise early (counters then sit below the constants: 97.4).
fix: int win[2] = {0, 0}; win[0]++ / win[1]++; if (win[0] == 2 || win[1] == 2); no pragma, no inner loop -> 100. Also measured: full-unroll limit is IR size (2 extra stores still unroll, 3 do not); copies/named temps/inline accessors are folded before the decision; any inner loop that indexes the array by a variable also blocks the outer unroll
