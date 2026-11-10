import re,sys,importlib.util,io,contextlib
spec=importlib.util.spec_from_file_location('simg','/private/tmp/scratch-0EFC/simg.py')
sg=importlib.util.module_from_spec(spec); sys.argv=['x',sys.argv[1]] if len(sys.argv)>1 else sys.argv
with contextlib.redirect_stdout(io.StringIO()): spec.loader.exec_module(sg)
def assign(nodes,col):
    reg={};used=set()
    for n in col:
        taken=set()
        for x in nodes[n]['nb']:
            if x<32: taken.add(x)
            elif x in reg: taken.add(reg[x])
        act=nodes[n]['reg']
        if act<14 and act not in (1,2,13):  # volatile: trust actual
            reg[n]=act; continue
        r=None
        for c in sorted(used):
            if c not in taken: r=c;break
        if r is None:
            for c in range(31,13,-1):
                if c not in taken and c not in used: r=c;break
        reg[n]=r; used.add(r)
    return reg
def run(nodes,T=28):
    col=sg.colorder(nodes,T); return assign(nodes,col)
if __name__=='__main__':
    nodes,_=sg.load(sys.argv[1])
    for T in (27,28,29):
        reg=run(nodes,T)
        bad=[(n,reg[n],nodes[n]['reg']) for n in reg if reg[n]!=nodes[n]['reg']]
        print(T,len(bad),bad[:8])
