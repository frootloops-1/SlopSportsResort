# Struct-stored ptmf call

- status: works
- tags: ptmf,__ptmf_scall
- scope: RPSportsCommon_unsplit

symptom: addi r12,rX,off; bl __ptmf_scall
cause: pointer-to-member stored inline in object
fix: typedef void (Owner::*Fn)(); (self->owner->*self->pmf)()
