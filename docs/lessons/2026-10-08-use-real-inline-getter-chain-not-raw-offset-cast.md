# Use real inline getter chain, not raw offset cast

- status: works
- tags: mwcc,regalloc,inline-getter

symptom: u16 local gets wrong callee-saved priority vs strength-reduced offsets; scoping/order changes do nothing
cause: field read via cast to local view struct instead of the real inline accessors
fix: mpHeads[0][k]->GetGenInfo().GetLocation().GetIndex() -> exact
