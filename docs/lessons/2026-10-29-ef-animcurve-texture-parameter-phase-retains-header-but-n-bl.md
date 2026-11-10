# ef_animcurve Texture parameter phase retains header but n blocks table colours

- status: fails
- tags: ef_animcurve,Texture,register-allocation,copy-propagation
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Header is folded into oldest pCmdList, while n/tick claim highest saved register.
cause: Overwriting command parameter with particle after frame calculation blocks first copy propagation; particle assignment later disappears, leaving fresh header. n still colours first among remaining roles.
fix: Particle phase gives header31/particle24 but n/tick30, tables29..26/seed25: 99.651474/46 lines vs baseline99.71850/42. Cache unsigned tickF then reuse tick for n: 95.509384/76, unchanged wrong GPR map plus conversion/FPR reorder. Both reverted. Trace observes particle copy removal and fresh header retention; original baseline header deletion stage untraced. Future only: n scalar reference with proven header phase.
