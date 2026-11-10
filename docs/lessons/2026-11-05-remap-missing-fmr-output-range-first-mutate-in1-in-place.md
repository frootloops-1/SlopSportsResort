# Remap missing fmr: output range first, mutate in1 in place

- status: works
- tags: rpgol,802b1a0c
- scope: Pack/RPSports/RPGolScene/RPGol_802b1a0c

symptom: missing fmr copy of out1 in remap (fn_802B3FF4)
cause: param order drives copy
fix: golRemapOut(out0,out1,in0,in1,v){in1 -= in0; if(0.0f==in1) return out0; return out0+(out1-out0)*(v-in0)/in1;} found by 120-order fn_harness sweep
