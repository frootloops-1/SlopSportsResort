import sys,copy
sys.path.insert(0,'/private/tmp/scratch-0EFC')
import importlib.util
spec=importlib.util.spec_from_file_location('sim','/private/tmp/scratch-0EFC/sim.py')
sim=importlib.util.module_from_spec(spec); sys.argv=['x','/private/tmp/scratch-0EFC/dbg0/regalloc-fpr-pass-1-assigned.txt']
import io,contextlib
with contextlib.redirect_stdout(io.StringIO()): spec.loader.exec_module(sim)
base,_=sim.load('/private/tmp/scratch-0EFC/dbg0/regalloc-fpr-pass-1-assigned.txt')
def renum(nodes,mp):
    out={}
    for n,d in nodes.items():
        nn=mp.get(n,n)
        out[nn]={'reg':d['reg'],'name':d['name'],'nb':[mp.get(x,x) for x in d['nb']]}
    return out
def run(nodes,watch):
    col=sim.colorder(nodes); reg=sim.assign(nodes,col)
    return {k:reg[v] for k,v in watch.items()}
# targets (retail)
W={'m':63,'c15':191,'a':66,'px':65,'py':64,'cx':68,'cy':67,
   'sy2':56,'ox2':55,'oy2':54,'w2':53,'h2':52,'sx2':51,'v':50,'x':49,'y':48,'t':47,'d2':278,'r16':281,'c16':283,'st':285,
   'sy3':40,'ox3':39,'oy3':38,'h3':36,'sx3':35}
T={'m':18,'c15':19,'a':22,'px':21,'py':20,'cx':24,'cy':23,'sy2':25,'ox2':20,'oy2':21,'w2':22,'h2':23,'sx2':24,'v':18,'x':19,'y':30,'t':19,'d2':29,'r16':28,'c16':27,'st':26,'sy3':24,'ox3':20,'oy3':21,'h3':22,'sx3':23}
def show(tag,nodes,mp={}):
    r=run(nodes,{k:mp.get(v,v) for k,v in W.items()})
    bad={k:(r[k],T[k]) for k in T if k in r and r[k]!=T[k]}
    print(tag,'bad',len(bad),bad)
show('base',base)
for newm in [100,150,183,185,189,190]:
    mp={63:newm+0.5}; show('m->%d'%newm, renum(base,mp),mp)
# sy last in panels: swap numbering so sy is lowest
p2={56:50.9,55:56,54:55,53:54,52:53,51:52}
p2={56:51,55:56,54:55,53:54,52:53,51:52}
show('sylast',renum(base,p2),p2)
p2b=dict(p2); p2b[63]=185.5
p3={40:35,39:40,38:39,36:38,35:36}
p2b.update(p3)
show('sylast+m185+p3',renum(base,p2b),p2b)
for newm in [192.5, 250.5, 400]:
    mp={63:newm}; mp.update({56:51,55:56,54:55,53:54,52:53,51:52,40:35,39:40,38:39,36:38,35:36})
    show('m->%s+sylast'%newm, renum(base,mp),mp)
mp={56:51,55:56,54:55,53:54,52:53,51:52,40:35,39:40,38:39,36:38,35:36, 191:62.5}
show('c15->62.5+sylast', renum(base,mp),mp)
import copy
for drop in [187, 186, 77, 191]:
    b2=copy.deepcopy(base)
    b2[63]['nb']=[x for x in b2[63]['nb'] if x!=drop]; b2[drop]['nb']=[x for x in b2[drop]['nb'] if x!=63]
    mp={63:138.5}; mp.update({56:51,55:56,54:55,53:54,52:53,51:52,40:35,39:40,38:39,36:38,35:36})
    show('m->138.5 drop %d +sylast'%drop, renum(b2,mp),mp)
