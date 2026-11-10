# resort: singleton name strings can be fully qualified (Sp2::Fld::Ddg::Scene) and prove namespace+class

- status: works
- tags: resort,singleton,naming,frisbee
- scope: resort
- source: can-fld

symptom: need a proven namespace for a sport
cause: the create passes the full qualified name to fn_80370BD8
fix: rename ctor/dtor symbols (__ct__Q43Sp23Fld3Ddg5SceneFv); Frisbee Dog lives in src/Sports2/Fld/Ddg/. Check every sport's singleton strings for qualified names
