# MWCC: this->field load orders before global store; only const-pointer param loads are free

- status: fails
- tags: mwcc,schedule,alias,stw,RPGrpModelRfl,drawgx
- scope: RPGrpModelRfl::DrawGX

symptom: retail stw spDrawModel issues next to lis (before lbzx); ours waits until after addi, 2-line diff in DrawGX
cause: in a non-const member fn a this->field load and a store to any global are always ordered (store waits ~2 cycles); statement order/temps/types irrelevant. Only loads through a const-pointer PARAMETER (or this in a const method) are free; harness-verified on GC 2.7/3.0a3/3.0a5, Wii 1.0/1.1
fix: open. No legit source found: table scope/form, temps, const locals/casts/fields, inline const helpers, setters, pointer-to-global, pragmas (opt_pointer_analysis on overshoots and segfaults at file top) all fail. Permuter not applicable (memory dependency). Harness: scratchpad/h/run.sh uses real flags -inline deferred -use_lmw_stmw on -str reuse,pool,readonly -lang=c++
