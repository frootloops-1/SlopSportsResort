# In-place modulo and compound forms: j=idx+i; j%=N; idx++; idx%=N; max*=k; return max

- status: works
- tags: modulo,regalloc,loop
- source: RPBsb_80259bbc

symptom: unrolled modulo loop mr+addi pattern / mulhw into same reg / fmuls into callee-saved FPR
cause: expression form changes dest reg reuse
fix: write in-place statements (int j=idx+i; j%=N;), idx++; idx%=500; max*=k; return max; bind Vector3f& v=arr[i] for one base load
