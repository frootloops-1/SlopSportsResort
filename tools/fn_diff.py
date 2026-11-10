#!/usr/bin/env python3
"""Rebuild one object and diff one function against the original, instruction by instruction.
Operands that are relocations are normalised (symbol names dropped), so only real differences show.
Usage: fn_diff.py UNIT_SRC_PATH FUNCTION_NAME [-n MAX_LINES]
  UNIT_SRC_PATH like unk/sinit_8051B8B4.cpp"""
import re, subprocess, sys, os, tempfile, difflib
unit, fn = sys.argv[1], sys.argv[2]
n = int(sys.argv[sys.argv.index('-n') + 1]) if '-n' in sys.argv else 60
obj = 'build/RZTE01_01/src/' + re.sub(r'\.(c|cpp)$', '', unit) + '.o'
r = subprocess.run(['ninja', obj], capture_output=True, text=True)
if r.returncode:
    print('\n'.join(l for l in r.stdout.split('\n') if re.search(r'In:|Error|^#\s+\d+:|\(\d{5}\)', l))[:2000]); sys.exit(1)
out = tempfile.mkdtemp()
mine_file = os.path.join(out, 'out.s')
subprocess.run(['build/tools/dtk', 'elf', 'disasm', obj, mine_file], capture_output=True)
def body(path, name):
    L = open(path).read().split('\n')
    try: i = next(i for i, l in enumerate(L) if re.match(rf'^\.fn {re.escape(name)},', l))
    except StopIteration: return None
    res = []
    for l in L[i + 1:]:
        if l.startswith('.endfn'): break
        m = re.match(r'/\*.*?\*/\s*(.*)', l)
        if m:
            ins = m.group(1)
            ins = re.sub(r'("[^"]+"|[A-Za-z_@][\w$@<>,:.]*?)(@ha|@l|@h|@sda21)\b', r'SYM\2', ins)
            ins = re.sub(r'\b(lbl|fn|func|jumptable|switch)_[\w$@.]*', 'SYM', ins)
            ins = re.sub(r'\.L_[0-9A-F]+', 'L', ins)
            ins = re.sub(r'(bl?|b[a-z]+)\s+\S+', lambda m: m.group(0).split()[0] + ' T', ins) if re.match(r'b', ins) else ins
            res.append(ins)
    return res
orig_file = subprocess.run(['grep', '-rlE', rf'^\.fn {re.escape(fn)},', 'build/RZTE01_01/asm'], capture_output=True, text=True).stdout.split()
a = body(orig_file[0], fn) if orig_file else None
b = body(mine_file, fn) if mine_file else None
if a is None or b is None: print('function not found:', 'orig' if a is None else 'mine'); sys.exit(1)
d = [l for l in difflib.unified_diff(a, b, 'orig', 'mine', lineterm='', n=1)]
same = sum(1 for x, y in zip(a, b) if x == y)
print(f'{fn}: orig {len(a)} insns, mine {len(b)}; ' + ('MATCH (normalised)' if a == b else f'{len(d)} diff lines'))
print('\n'.join(d[:n]))
