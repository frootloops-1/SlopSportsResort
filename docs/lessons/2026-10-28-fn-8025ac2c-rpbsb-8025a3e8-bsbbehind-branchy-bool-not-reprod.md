# fn_8025AC2C (RPBsb_8025a3e8): BsbBehind branchy bool not reproducible by any direct bool form

- status: fails
- tags: fn_8025AC2C,RPBsb_8025a3e8,bool,fcmpo,cror
- scope: RPBsb_8025a3e8
- source: claude/bsb2-1028 sonnet

symptom: target bge;li 1;b;li 0;cmpwi;beq vs ours cror eq,gt,eq;mfcr;extrwi;cntlzw;srwi.
cause: CW collapses direct bool forms to the mfcr/srwi (x<c) or cror/extrwi (!(x>=c)) idiom
fix: failed: !(x>=c), x<c, ?: true/false both ways, if/else return, int return, bool r assign, local f32 d, with/without != false at call site, x<c&&true, x<c||false. Near misses: 'bool r; if(c) r=true; else r=false;' folds into caller if (96.1); 'bool r=false; if(x<c) r=true; return r;' keeps cmpwi join but li 0 hoisted (97.6). Original stays best 97.7
