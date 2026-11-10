# resort: Unk_80257BC8 list-index scheduling residue (RPGrpShadowTexture)

- status: fails
- tags: resort,regalloc,scheduling,RP
- source: rp-shadowtexture worker 2026-11-09

symptom: original lwz r4,0x44(r4) before stmw; mulli r3/lwz r0/add vs ours mulli r0/lwz r3/add
cause: unknown; real m_mdlList member, inline helper with local idx, single expression all unchanged
fix: parked at 87%; try the regalloc playbook or a different statement order around the stmw
