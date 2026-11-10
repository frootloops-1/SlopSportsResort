# fn_8033DB38 96.4: BowSphRef holder closes the GPR wall; FPR velocity block remains

- status: open
- tags: holder,coalescing,fpr,scheduler,fn_8033DB38,R17,RPBow
- scope: Pack/RPSports/RPBowScene/RPBow_8033B690
- source: wave3 2026-11-01

symptom: 96.0%, 262 diff lines; si/sj coloured last
cause: named locals r32-r41 rank below all IRO temps and coalescenodes keeps the lower vreg of a mr pair so the a-loop iterator @2689 merged into named si. Remaining FPR block: original computes velI = cpI - oI first (tmpI slot 0xa4) but delays the I.z chain, J.xy sub in f6 with n.yz f5; velI-first source gives a different pre-RA DAG (I.z early, J in f5)
fix: BowSphRef{BowPinSphere* p} holders (R17 row 72). Dead: all 30 dependency-legal orders of velI/velJ/rel/vj/vi/vr (best stays 126, velI-first 93.5-95.2), vi/vj declared up front, BowAbsDot inline (146), explicit VEC3Sub into tI/tJ (222, stack slots shift), no holder variants (swap si/sj r20/r19; pi->sph[a] 95.6; holder on one side 96.2/96.0). Next: dump the velI-first variant with mwcc_dbg (/tmp/d3scratch/dump1) and look for an IR-shape change lowering the I.z chain height or different inline nesting for operator-/VEC3Sub; keep VEC3 copy count and slots (tmpI 0xa4, tmpJ 0x98, velI 0x194, velJ 0x17c); else park
