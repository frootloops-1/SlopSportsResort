# fn_802B2F90 (RPGol_802b1a0c): read a named local through an inline member getter so it is coloured before an inline-parameter temp

- status: works
- tags: RPGol_802b1a0c,regalloc,mwcc_dbg,inline-getter
- scope: RPGol

symptom: 99.91%: sound manager r26 vs target r25
cause: bp (r70) coloured first took r26; the inline's sound-manager param temp @1887 (r43) reused r26 because bp is dead; pp (named, r36) came last and took r25. Target needs the sound manager in r25, so pp must be coloured before @1887.
fix: pp = pl->GetPos() with GolPlayer::GetPos(){return f4c;} (member getter, name inferred) -> 100%. Dead end: assigning the inline arg to a named local first (GolSnd* snd = spInstance) does nothing, it is copy-propagated. Commit 679ed48bf on claude/g2f90-1029. Worker added no marker; orchestrator to decide on MATCH-PENDING/ledger.
