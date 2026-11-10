# fn_802C5C78: sq as inline param + x-first dots fixes callee-saved FPR roles

- status: works
- tags: fn_802C5C78,rpgol,colouring,fpr,inline-param,sq
- scope: RPGol_802c58d4

symptom: sq f30/y-abs f31/x f29 wanted; named sq coloured after the abs temps so y-abs reused f30
cause: named locals colour after inline temps; allocator reuses lowest already-used callee-saved reg; nodes with >=32 neighbours (dist, t) colour first
fix: golDist(ax, ay, sq) inline owns the sqrt guard, call golDist(golAbs(x), golAbs(y), XZLenSq(v)) without a named sq; dots x first then y; VecDot2 decl w3,w0,w1,w2 -> 99.5->99.6 (partial; schedule+FPR roles match, volatile numbering hunks remain). objdiff percent can drop when schedule differs even if diff lines fall: y-dot first gave 97.7
