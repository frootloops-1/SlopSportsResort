# if(call) return K; return 0 is if-converted; orig shape is switch(call){case 0:break; default: return K;} return 0;

- status: works
- tags: rpgolmapobjtree,switch,if-conversion
- scope: RPGolMapObjTree
- source: opus

symptom: cmpwi/beq/li K/b/li 0 shape not produced by if/ternary/bool
cause: MWCC if-converts to neg/or/srawi/mask
fix: switch(call){case 0: break; default: return K;} return 0; plus dont_inline on defs called via bl
