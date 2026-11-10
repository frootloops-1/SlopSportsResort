# fn_8031A0E0 v1BC/v1C8 ps_mr is a pre-RA schedule outcome, flat to statement/c-placement edits

- status: fails
- tags: RPBow_80319C98,fn_8031A0E0,ps_mr,schedule,coalesce
- scope: RPBow_80319C98

symptom: extra ps_mr f0,f1 in v1BC += (v188-v1BC)*c; retail coalesces it and keeps the v1C8 scaled reload
cause: scheduler puts the BC z ps_sub (redefines the sub temp) between the forwarded ps_mr and ps_muls0 -> interference -> copy not coalesced
fix: Dead: c local in 5 positions, prm->pC4 inline, all valid v1D4/c/lerp statement perms, approach helpers (ref/ptr/by-value, +90 diffs), named sub/scale temps, v1D4 = VEC3(...)
