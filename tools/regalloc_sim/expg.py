import sys,copy,importlib.util,io,contextlib
spec=importlib.util.spec_from_file_location('s2','/private/tmp/scratch-0EFC/simg2.py')
s2=importlib.util.module_from_spec(spec); sys.argv=['x','/private/tmp/scratch-0EFC/dbg3/regalloc-gpr-pass-1-assigned.txt']
with contextlib.redirect_stdout(io.StringIO()): spec.loader.exec_module(s2)
base,_=s2.sg.load(sys.argv[1])
def renum(nodes,mp):
    out={}
    for n,d in nodes.items():
        out[mp.get(n,n)]={'reg':d['reg'],'name':d['name'],'nb':[mp.get(x,x) for x in d['nb']]}
    return out
def check(tag,nodes,mp={}):
    for T in (27,28,29):
        reg=s2.run(nodes,T)
        tgt={mp.get(n,n):base[n]['reg'] for n in base}
        tgt[mp.get(61,61)]=28
        bad=[(n,reg[n],tgt[n]) for n in reg if reg[n]!=tgt[n]]
        print(tag,T,len(bad),bad[:6])
for num in [58.5, 63.5, 100.5, 150.5, 202.5, 210.5, 230.5, 300.5]:
    mp={61:num}; check('r61->%s'%num, renum(base,mp), mp)
def merge(nodes,a,b):
    # merge b into a
    out=copy.deepcopy(nodes)
    nb=set(out[a]['nb'])|set(out[b]['nb']); nb.discard(a); nb.discard(b)
    out[a]['nb']=sorted(nb)
    del out[b]
    for n,d in out.items():
        if b in d['nb']:
            d['nb']=sorted(set(a if x==b else x for x in d['nb'])-{n})
    return out
m=merge(base,73,61)
for T in (27,28,29):
    reg=s2.run(m,T)
    tgt={n:base[n]['reg'] for n in m}
    bad=[(n,reg[n],tgt[n]) for n in reg if reg[n]!=tgt[n]]
    print('merge73',T,len(bad),bad[:6])
print(base[61]['nb'])
import itertools
cands=[x for x in base[61]['nb'] if x>=32]
for k in (1,2):
    for drop in itertools.combinations(cands,k):
        b2=copy.deepcopy(base)
        b2[61]['nb']=[x for x in b2[61]['nb'] if x not in drop]
        for d in drop: b2[d]['nb']=[x for x in b2[d]['nb'] if x!=61]
        ok=[]
        for T in (27,28,29):
            reg=s2.run(b2,T); tgt={n:base[n]['reg'] for n in b2}; tgt[61]=28
            bad=[(n,reg[n],tgt[n]) for n in reg if reg[n]!=tgt[n]]
            ok.append(len(bad))
        if min(ok)==0: print('drop',drop,ok)
