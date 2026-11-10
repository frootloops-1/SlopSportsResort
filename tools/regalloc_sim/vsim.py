import re,sys
def load(path):
    nodes={};order=[]
    cur=None
    for line in open(path):
        m=re.match(r'^r(\d+) -> r(\d+)\s*(\S*)',line)
        if m:
            cur=int(m.group(1)); nodes[cur]={'reg':int(m.group(2)),'name':m.group(3),'nb':[]}; order.append(cur); continue
        m=re.match(r'^  neighbors: \d+ \((.*)\)',line)
        if m and cur is not None:
            nodes[cur]['nb']=[int(x[1:]) for x in m.group(1).split() if x.startswith('r')]
    return nodes,order
def colour(nodes,order):
    reg={}
    for n in order:
        if n<32: continue
        act=nodes[n]['reg']
        if act>=13 or act in (1,2): reg[n]=act; continue
        taken=set()
        for x in nodes[n]['nb']:
            if x<32: taken.add(x)
            elif x in reg: taken.add(reg[x])
        cands=([0] if act==0 else [])+list(range(3,13))
        r=next((c for c in cands if c not in taken),None)
        reg[n]=r
    return reg
if __name__=='__main__':
    nodes,order=load(sys.argv[1])
    reg=colour(nodes,order)
    bad=[(n,reg[n],nodes[n]['reg']) for n in order if n>=32 and reg[n]!=nodes[n]['reg']]
    print('mismatch',len(bad),bad[:20])
