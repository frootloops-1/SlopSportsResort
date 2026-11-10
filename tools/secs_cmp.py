"""Compare section sizes of a BTE src build against the original split object.
usage: python3 tools/secs_cmp.py bta/sys/bd main/bte_logmsg  (paths under revolution/BTE)
.comment is ignored; any other mismatch means extra/missing code or data."""
import subprocess,sys,re
def secs(p):
    o=subprocess.run(['build/binutils/powerpc-eabi-objdump','-h',p],capture_output=True,text=True).stdout
    d={}
    for l in o.splitlines():
        m=re.match(r'\s*\d+ (\.\w+)\s+([0-9a-f]{8})',l)
        if m and int(m[2],16): d[m[1]]=int(m[2],16)
    return d
for u in sys.argv[1:]:
    a=secs(f'build/RZTE01_01/src/revolution/BTE/{u}.o'); b=secs(f'build/RZTE01_01/obj/revolution/BTE/{u}.o')
    diff={k:(a.get(k),b.get(k)) for k in set(a)|set(b) if k!=".comment" and a.get(k)!=b.get(k)}
    print(u,'OK' if not diff else diff)
