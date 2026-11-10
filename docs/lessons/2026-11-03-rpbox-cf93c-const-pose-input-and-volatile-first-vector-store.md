# RPBox cf93c: const pose input and volatile first vector store improve two residues

- status: works
- tags: RPBox_802cf93c,fn_802D1BD8,fn_802D7B24,const,volatile,FPR,R17
- scope: RPBox_802cf93c
- source: 2026-11-03 codex-rpbox-cf93c-20261103; build/evidence/rpbox-pass

symptom: D1BD8 98.37322 with scheduling/register differences; D7B24 98.74667 and four bytes short from eliminated initial d.x store.
cause: Const pointee changes scheduler/VN load flags. Ordinary local access eliminates the first d.x write; volatile store preserves it without an added load.
fix: D1BD8 const BoxObj* self in both declarations/definition gives99.47293; pass s.x*v.x+cw directly to PodVEC3Scale gives99.54416 (plain C++). D7B24 first write through volatile f32* gives98.98444 and1800B=target, R17. All148 exact funcs preserved, data100, order0. Residues remain; not a full match.
