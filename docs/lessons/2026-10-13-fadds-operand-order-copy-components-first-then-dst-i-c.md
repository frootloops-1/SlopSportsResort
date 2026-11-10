# fadds operand order: copy components first, then dst[i] += c

- status: works
- tags: float,fadds,order
- scope: RPGol_802c6e28
- source: claude/rpgolscene-unsplit

symptom: fadds f0,f0,f2 vs f2,f0 when writing y = v[1] + 0.5f
cause: expression form decides operand order
fix: copy all components first, then dst[1] += 0.5f; expression reorders and temps did not help
