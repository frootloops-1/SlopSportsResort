# MWCC allocator: local type decides merge into load temp; permuter never explores decl order/types

- status: works
- tags: register,regalloc,vreg,declaration-order,type,permuter,harness
- scope: global
- source: docs/llm_matching_tricks.md (Forecast decomp)

symptom: same instructions, wrong register numbers; permuter only ties; shape changes don't move one local
cause: Select colours descending vreg (lowest free volatile; callee-saved r31 down). Named locals: first declared = highest vreg; @N inline/optimizer vars below; expression temps above all. A local assigned from a load merges into the load temp if its type allows (coloured first)
fix: Declare locals up front uninitialised in chosen order, assign later; flip local types (wchar_t/u32, s32/u32, typed ptr/void*); sweep orders/types with a 0.5 s one-function harness. See docs/regalloc-playbook.md, docs/llm_matching_tricks.md
