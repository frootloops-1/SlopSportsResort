import sys,os
sys.path.insert(0,os.path.dirname(os.path.abspath(__file__)))
from vsim import load,colour
nodes,order=load(sys.argv[1])
names={int(k):v for k,v in (x.split('=') for x in sys.argv[2].split(','))}
def show(tag,o):
    reg=colour(nodes,o)
    print(tag,' '.join('%s:r%d'%(names[n],reg[n]) for n in names))
show('orig',order)
for mv in sys.argv[3:]:
    a,b=map(int,mv.split('<'))   # put a right before b
    o=[x for x in order if x!=a]; o.insert(o.index(b),a)
    show(mv,o)
