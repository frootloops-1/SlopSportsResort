# Lerp/invlerp/min/max inline helpers reproduce golf float code

- status: works
- tags: float,inline,fmadds
- scope: RPGolScene
- source: claude/rpgol-family

symptom: constant load order or fmadds operand order wrong when lerp written inline
cause: original used small inline helpers
fix: GolInvLerp(v,a,b)=(v-a)/(b-a); GolLerp(a,b,t){float d=b-a; return d*t+a;}; GolMax(a,b){return a<b?b:a;} gives bge;b;fmr; GolMin(a,b){return a>b?b:a;} gives ble;b;fmr
