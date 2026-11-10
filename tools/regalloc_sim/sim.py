import re,sys
def load(path):
    nodes={};order=[]
    cur=None
    for line in open(path):
        m=re.match(r'^f(\d+) -> f(\d+)\s*(\S*)',line)
        if m:
            cur=int(m.group(1)); nodes[cur]={'reg':int(m.group(2)),'name':m.group(3),'nb':[]}; order.append(cur); continue
        m=re.match(r'^  neighbors: \d+ \((.*)\)',line)
        if m and cur is not None:
            nodes[cur]['nb']=[int(x[1:]) for x in m.group(1).split()]
    return nodes,order
def sim(nodes,T):
    removed=set(); passes=[]
    remaining=sorted(n for n in nodes if n>=32)
    while remaining:
        p=[]
        for n in remaining:
            deg=sum(1 for x in nodes[n]['nb'] if x<32 or x not in removed)
            if deg<T:
                removed.add(n); p.append(n)
        if not p: return passes, remaining
        passes.append(p); remaining=[n for n in remaining if n not in removed]
    return passes,[]
nodes,order=load(sys.argv[1])
for T in range(26,36):
    passes,stuck=sim(nodes,T)
    col=[]
    for p in reversed(passes): col+=list(reversed(p))
    real=[n for n in order if n>=32]
    ok=sum(1 for a,b in zip(col,real) if a==b)
    print(T,len(passes),len(stuck),ok,len(real))

def assign(nodes, col, phys_used_first=None):
    reg={}
    used=set()
    for n in col:
        taken=set()
        for x in nodes[n]['nb']:
            if x<32: taken.add(x)
            elif x in reg: taken.add(reg[x])
        r=None
        for c in range(0,14):
            if c not in taken: r=c;break
        if r is None:
            for c in sorted(used):
                if c not in taken: r=c;break
        if r is None:
            for c in range(31,13,-1):
                if c not in taken and c not in used: r=c;break
        reg[n]=r
        if r>=14: used.add(r)
    return reg
def colorder(nodes,T=32):
    passes,stuck=sim(nodes,T)
    col=[]
    for p in reversed(passes): col+=list(reversed(p))
    return col
if __name__=='__main__':
    col=colorder(nodes)
    reg=assign(nodes,col)
    bad=[(n,reg[n],nodes[n]['reg']) for n in col if reg[n]!=nodes[n]['reg']]
    print('mismatch',len(bad),bad[:10])
