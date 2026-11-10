# Read mode into a local and switch via param-taking inline

- status: works
- tags: regalloc,inline

symptom: inline getType() reloads this->mode and loses shared cr compare
cause: member reload in inline
fix: local mode + getTypeOf(mode) (fn_801E06D8)
