# fn_8025C934/fn_8025AE54 C residues are scheduling only

- status: fails
- tags: fn_8025C934,fn_8025AE54,RPBsb_8025a3e8,scheduling
- scope: RPBsb_8025a3e8
- source: claude/bsb5a3-c-1107 opus

symptom: C934: prev x,z,y stores + old/t.x f0/f2 swap (12 diffs); AE54: first volatile m[3] load hoisted above prologue moves (2 diffs)
cause: list scheduler tie-breaks; unknown source shape
fix: failed C934: perms of prev stores/loads/decls (216), prev=cur struct assign (29), old-load placement perms (28). AE54: plain ctor/assign/pointer-helper pos (8, loads batched; retail serialises via f0), opt_prolog on/off no effect
