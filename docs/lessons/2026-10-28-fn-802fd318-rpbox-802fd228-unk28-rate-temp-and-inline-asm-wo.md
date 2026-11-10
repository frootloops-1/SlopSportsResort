# fn_802FD318 (RPBox_802fd228): unk28*rate temp and inline-asm work0 colour before the named component locals

- status: fails
- tags: regalloc,fpr
- scope: RPBox_802fd228 fn_802FD318
- source: FPR batch 2 2026-10-28

symptom: 99.17, leaf function, no calls
cause: a named single-use local is copy-propagated back to a temp, so it cannot be demoted; target colours them after `one`
fix: none: bx before one (99.0), named scaled, direct-store copies (92.5), BoxLerp for rate (98.8), in-function asm block (98.7)
