# fn_8024929C (RPTns_80249284): const TnsVec3* target fixes the 3-load struct copy; then the hoisted-locals workaround became the residue (plain source, 100)

- status: works
- tags: rptns,8024929c,const,alias,struct-copy,hoist
- source: worker cs1 2026-10-31 (constsweep)

symptom: 98.5%: cur = *target copied pairwise (lwz pairs) and target loads hoisted together; 64-subset hoist sweep and copy spellings all <= 98.5
cause: non-const pointee: Alias.c keeps program order for the loads; with const pointee the target's 3-register load-all-then-store copy and early/late target loads appear. The hoisted px..tz locals added to steer the non-const schedule then blocked the match
fix: void fn_8024929C(TnsRacketBase* self, const TnsVec3* target); drop the px/py/pz/tx/ty/tz locals: self->f50.x = self->pos.x + off.x ...; d.x = self->f50.x - target->x ... (tnsAdd/tnsSub form also 100). After a constness fix re-test the plain source with workaround locals removed. Earlier dead ends (64-subset hoist sweep, tnsAdd/tnsSub 96.0, copy spellings) were on a non-const pointee and are obsolete. No marker.
