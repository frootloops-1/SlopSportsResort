# fn_8031A0E0 c-load after v1D4.z store: alias-breaking spellings flat (round 7)

- status: fails
- tags: scheduler,alias,RPBow_80319C98
- scope: Pack/RPSports/RPBowScene/RPBow_80319C98

symptom: pre-RA scheduler hoists prm->pC4 load (0xc4(r31)) above stfs 0x1dc(r29); retail keeps it after, which would remove both v1BC/v1C8 ps_mr
cause: MWCC knows prm = self+0x258 regardless of how the store/load is spelled, so it never adds the store->load dependence
fix: Dead (harness 112, identical): VEC3& t / VEC3* t = &self->v1D4 for the x/y/z writes, local-struct static inline Add(VEC3&, const VEC3&, f32), f32* pz = &v1D4.z, const BowCamParams& p = *prm, c via local-struct getter on prm, c via (BowCamParams*)((char*)self + 0x258). Parked.
