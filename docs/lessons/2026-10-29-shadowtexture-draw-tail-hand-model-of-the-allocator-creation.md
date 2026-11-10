# ShadowTexture Draw tail: hand model of the allocator (creation order table) says flag values must be created first, schedule says row first; 48-point grid finds no joint solution

- status: fails
- tags: shadowtexture,draw,regalloc,scheduler,debugger
- scope: egg/gfxe/eggShadowTexture

symptom: Draw's last capture block: opcode stream OK in the named-row form (22 lines) but volatile regs wrong; inline-row form fixes row regs (17 lines) but add/rlwinm/sth order differs
cause: Debugger numbering: temps are numbered in statement-creation order, coloured descending, each takes the lowest free of r0,r3.. . Target colouring needs creation order {flag lhz G, G'} lowest, then format chain F,S,U,O,I, then L, with C (cntlzw) coloured before G; target schedule (lbz, cntlzw, lis, lhz, ..., add before the index rlwinm, sth last) is what the named-row form (rows created first) produces. Moving disablePixModeSync() first fixes colours (lbz lands r4) but the scheduler then emits lis before cntlzw, addi early and add after sth. Scheduler tie-breaks are not creation-order only, so the two requirements conflict for every spelling tried
fix: none: 6 statement orders x row named/inline x 4 intensity forms (48), swapped-subscript and pointer-add forms, inline probe of the flag clear (forwarded, no effect), flags-first forms. tools/regalloc_diag.py needs --target build/RSPE01_01/obj/<unit>.o --ours build/RSPE01_01/src/<unit>.o here (defaults are wrong) and reports VOLATILE-ONLY with swap hints (r0<->r6, r4<->r5). Next: a construct that moves only the flags load/store earlier in creation without moving it in the schedule (private mFlags blocks a named-local probe), or accept as a scheduler wall
