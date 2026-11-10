# resort library: port_flip deletes split lines its object lacks; port_flip_ext copies over tracked src

- status: works
- tags: resort,library,port

symptom: lost .data range (g3d_restev 806B35C0); clobbered source
cause: tool rewrites stanza and copies ogws file
fix: re-add split lines by hand; restore src with git checkout, not rm
