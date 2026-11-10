# HID trace calls and WBT device-information record

RSPE01_01, codex-nearmiss-round4-1019; evidence build/evidence/round4/.

The generic HIDD_TRACE(level, ...) macro emits no code; its header's assumption that retail lacks these traces is explicitly unverified. Original hidd_conn_initiate contains two trace blocks. Restore the numbered EVENT0/WARNING0 forms at the proven call sites. Recover the missing hidd_proc_repage_timeout with its DEBUG0 trace, retry limit15, timer22/one second and callback events1/2. A scoped dont_inline pragma around initiate preserves the original call boundary instead of inlining its body into timeout. Both original functions (392 bytes) and referenced strings/relocations match; full source-linked DOL equality permits Matching despite74.11168% raw data score from unused upstream strings.

The missing WBT_ExtCreateRecord uses a252-byte get-record containing a250-byte DI record. The shared upstream default SDP_MAX_ATTR_LEN400 is too large; define80 in this TU before BTE headers. Keep a record pointer scoped to the record-creation branch and preserve the original failure-path handle reset with a volatile local. Volatile is the chosen matching construction, not an asserted recovered original qualifier. All224 function bytes and five call relocations match. Change only the WBT split owner's.o extension to.c without moving its boundaries. Source-linked configured DOL equality proves completion; no shared header edit is required.

Both units source-link to the original DOL SHA1 8bb422971b88b5551a37de98db69557df7b46637. Extra source routines may be linker-discarded: distinguish required linked bytes from full raw ELF equality.
