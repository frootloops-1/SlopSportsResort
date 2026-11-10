# Two interleaved dot products: write the second one first

- status: works
- tags: float,dot,regalloc,order
- scope: Pack/RPSports/RPTnsScene/RPTns_8022a740
- source: claude-opus

symptom: s/k dot products (q.ax.z, q.ax.y) interleaved with different regs
cause: statement order sets accumulation registers
fix: k = Dot(q, ay) before s = Dot(q, az) with inline Dot(a,b); orig fmuls still starts with s
