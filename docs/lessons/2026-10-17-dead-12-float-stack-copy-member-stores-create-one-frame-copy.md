# dead 12-float stack copy: member stores create one frame copy per store

- status: fails
- tags: stack,dead-locals,frame,rpbsb
- source: RPBsb_8027d3ec 2026-10-17

symptom: fn_8027D9BC: orig one contiguous 0x30 dead copy, frame 0x40
cause: MWCC gives each dead member store its own copy of the aggregate (frame 0x250 for 12 stores); whole-object copies (POD or non-POD) are fully deleted
fix: failed (18 tries): member stores, loops, union, array init, ctor, copy-ctor members, RVO inline, by-value/by-ref unused inline param, by-value real 3rd param (gives contiguous 0x40 but adds r4 and interleaves). Still 95.7 with four ctor-built Vec locals
