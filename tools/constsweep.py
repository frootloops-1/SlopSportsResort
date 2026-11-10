"""Constness toggle sweep over near-miss functions.

MWCC 3.0a5.2 alias analysis treats loads through a const pointee as safe (the pre-RA scheduler
may float them above stores) and IRO_CommonSubs does not CSE const-qualified loads with plain
loads, so the original's constness is observable in the asm. This tool flips the constness of
ONE site at a time (definition and every declaration/thunk of it in the same file), rebuilds the
unit, and records how the function's asm_diff line count moves. It never leaves a change behind:
the file is restored after each trial. Each toggle is bidirectional (adds `const`, or removes an
existing one, so the reverse direction is covered).

Site kinds (--kinds, default all but cast):
  param   top-level pointer/reference parameters of the fn_* itself
  member  struct/class member pointers and references (`T* m;`) the body reaches through
          `->m` / `.m`, as declared in the unit's own source (one site per declaration)
  local   local pointer/reference variables declared in the body (`T* p = ...;`)
  helper  pointer/reference parameters of in-file functions the body calls (static inline helpers,
          methods defined in the file)
  method  `const` on in-file methods the body calls through `->`/`.` (`GetX() const`)
  ret     const on the pointer/reference RETURN type of in-file functions the body calls
  global  file-level `extern T x;` <-> `extern const T x;` (scalars, pointers, arrays) for every extern whose name the
          body uses, applied to ALL extern declarations of that name in the file, both directions. fn_802CDFC0 needed
          `extern f32 x` NON-const (an .sdata symbol; const hoisted its lfs); fn_80275810 needed `extern const f32/s32`
          declared at the top and DEFINED at file end with `__declspec(section ".sdata") const`. A pure toggle can
          fail to compile or change the section when the file also defines the symbol: such a site shows n=None or a
          worse n, so record the n and emulate the definition by hand if the direction looks promising.
  cast    `(T*)` casts in the body (opt-in)
Candidates are fn_* (extern "C") functions in NonMatching units (mangled C++ names change with
pointee constness, so those are skipped).

  ninja progress                      # refresh build/RZTE01_01/report.json first (stale otherwise)
  python3 tools/constsweep.py --make-cands cands.json [--min 96] [--max-size 3500]
  python3 tools/constsweep.py <shard> <nshards> <worktree> [--cands cands.json] [--logdir DIR]
        [--kinds param,member,...] [--only substr1,substr2] [--max-base 150] [--max-sites 80]
        [--deep 3]   # after a gain, keep the best change and re-sweep from it (greedy, N rounds);
                     # writes <logdir>/patch_<fn>.diff with the combined change
  python3 tools/constsweep.py --rank DIR   # ranked list of improvements from DIR/results*.jsonl

Run each shard in its OWN worktree (never two builds in one tree), e.g. four shards:
  for i in 0 1 2 3; do tools/setup_worktree.sh /private/tmp/ogws-cs$i-DATE claude/cs$i-DATE; done
  for i in 0 1 2 3; do nohup python3 tools/constsweep.py $i 4 /private/tmp/ogws-cs$i-DATE \
      --cands cands.json --logdir /tmp/cs > /tmp/cs/out$i.txt 2>&1 & done
Each shard writes <logdir>/shard<N>.log and <logdir>/results<N>.jsonl and ends with a DONE line.
Then: python3 tools/constsweep.py --rank /tmp/cs

Pitfalls handled: a variant that fails to compile leaves the old .o behind, so the .o is
deleted before each trial and a missing .o counts as invalid (n=None); the source is restored in
a finally block (and the worktree's src/ is reset at shard start: use a dedicated worktree);
macOS has no `timeout`. A toggle that would make the function itself write through a const
pointer fails to compile and shows n=None, which is expected for most param sites.
"""
import json, os, re, subprocess, sys

KINDS_DEFAULT = ['param', 'member', 'local', 'helper', 'method', 'ret', 'global']
KEYWORDS = {'return', 'else', 'case', 'delete', 'new', 'goto', 'sizeof', 'typedef', 'throw', 'do',
            'if', 'while', 'for', 'switch', 'static_cast', 'reinterpret_cast', 'const_cast',
            'defined', 'operator', 'typeof', 'asm', 'extern', 'sizeof'}


def make_cands(out, min_pct=96.0, max_size=3500):
    report = json.load(open('build/RZTE01_01/report.json'))
    nonmatching = set()
    for line in open('configure.py'):
        m = re.search(r'Object\(NonMatching,\s*"([^"]+)"', line)
        if m:
            nonmatching.add(re.sub(r'\.(cpp|c)$', '', m.group(1)))
    cands = []
    for u in report['units']:
        unit = u['name'].replace('main/', '', 1)
        if unit not in nonmatching:
            continue
        for f in u.get('functions', []):
            pct = f.get('fuzzy_match_percent', 100)
            if f['name'].startswith('fn_') and min_pct <= pct < 100 and int(f.get('size', 0)) <= max_size:
                cands.append((unit, f['name'], pct))
    cands.sort(key=lambda c: -c[2])
    json.dump(cands, open(out, 'w'))
    print(len(cands), 'candidates ->', out)


# ---------------------------------------------------------------------------------------------
# text analysis helpers

def split_params(s):
    out, depth, cur = [], 0, ''
    for ch in s:
        if ch in '(<[':
            depth += 1
        if ch in ')>]':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur)
            cur = ''
        else:
            cur += ch
    out.append(cur)
    return out


def toggle(p):
    """Toggle const on a top-level pointer/reference parameter text; None if not applicable."""
    q = p.strip()
    if not re.search(r'[\*&]', q) or '**' in q or '(*' in q:
        return None
    lead = re.match(r'\s*', p).group(0)
    if q.startswith('const '):
        return lead + q[6:]
    if q.startswith(('struct ', 'class ')):
        return None
    return lead + 'const ' + q


def mask(text):
    """Same-length copy with comments and string/char literal contents blanked (newlines kept)."""
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if text.startswith('//', i):
            j = text.find('\n', i)
            j = n if j < 0 else j
            for k in range(i, j):
                out[k] = ' '
            i = j
        elif text.startswith('/*', i):
            j = text.find('*/', i + 2)
            j = n if j < 0 else j + 2
            for k in range(i, j):
                if text[k] != '\n':
                    out[k] = ' '
            i = j
        elif c in '"\'':
            j = i + 1
            while j < n and text[j] != c and text[j] != '\n':
                j += 2 if text[j] == '\\' else 1
            for k in range(i + 1, min(j, n)):
                out[k] = ' '
            i = j + 1
        else:
            i += 1
    return ''.join(out)


def blocks(m):
    """List of (open, close, kind) for every {...} block; kind in type/ns/code."""
    res, stack = [], []
    last = 0
    for i, ch in enumerate(m):
        if ch == '{':
            head = m[last:i]
            head = '\n'.join(l for l in head.split('\n') if not l.lstrip().startswith('#'))
            if re.search(r'\b(struct|class|union)\b', head) and '(' not in head and '=' not in head:
                kind = 'type'
            elif re.search(r'\bnamespace\b', head) or (re.search(r'\bextern\b', head) and '(' not in head):
                kind = 'ns'
            else:
                kind = 'code'
            stack.append((i, kind))
            last = i + 1
        elif ch == '}':
            if stack:
                o, kind = stack.pop()
                res.append((o, i, kind))
            last = i + 1
        elif ch == ';':
            last = i + 1
    res.sort()
    return res


def enclosing(bl, pos):
    for o, c, kind in reversed(bl):
        if o < pos < c:
            return kind
    return 'file'


def looks_like_decl_params(params):
    """True if a parenthesised list looks like a parameter declaration list, not call arguments."""
    ps = split_params(params)
    for p in ps:
        q = p.strip()
        if not q or q == 'void' or q == '...':
            continue
        if '->' in q or '.' in q or q[0] in '&*-+0123456789!~(':
            return False
        if not (re.search(r'[\*&]', q) or len(q.replace('const', '').split()) >= 2):
            return False
    return True


def signatures(m, name):
    """Definitions/declarations of `name` (not calls): (name_start, params_start, params_end)."""
    res = []
    for mm in re.finditer(r'(?<![\w.>])' + re.escape(name) + r'\s*\(([^()]*)\)', m):
        before = m[:mm.start()].rstrip()
        after = m[mm.end():mm.end() + 80]
        if not looks_like_decl_params(mm.group(1)):
            continue
        if not re.match(r'\s*(?:const\b\s*)?(?:DECOMP_\w+\s*)?[;{:]', after) and not re.match(r'\s*(?:const\s*)?\w+\s*[;{]', after):
            continue
        # preceded by a type (identifier, *, &, > or ::) and not by an expression operator
        if not before or not (before[-1].isalnum() or before[-1] in '_*&>:~'):
            continue
        w = re.search(r'(\w+)$', before)
        if w and w.group(1) in KEYWORDS:
            continue
        if before.endswith(('::',)) or before[-1] != ':':
            res.append((mm.start(), mm.start(1), mm.end(1)))
    return res


def body_of(m, bl, fn):
    for ns, ps, pe in reversed(signatures(m, fn)):
        mm = re.match(r'\s*(?:const\s*)?(?:DECOMP_\w+\s*)?\{', m[pe + 1:])
        if mm:
            o = pe + 1 + mm.end() - 1
            for b in bl:
                if b[0] == o:
                    return o, b[1]
    return None


def apply_edits(text, edits):
    for s, e, r in sorted(edits, reverse=True):
        text = text[:s] + r + text[e:]
    return text


# ---------------------------------------------------------------------------------------------
# site generators: each yields (kind, label, new_text)

def param_edits(text, m, name, idx, ref_arity):
    edits = []
    for ns, ps, pe in signatures(m, name):
        pl = split_params(text[ps:pe])
        if len(pl) != ref_arity or idx >= len(pl):
            continue
        t = toggle(pl[idx])
        if t is None:
            return None
        pl[idx] = t
        edits.append((ps, pe, ','.join(pl)))
    return edits or None


def param_sites(text, m, name, kind, label_prefix=''):
    sigs = signatures(m, name)
    if not sigs:
        return
    ref = split_params(text[sigs[-1][1]:sigs[-1][2]])
    for idx, pp in enumerate(ref):
        if toggle(pp) is None:
            continue
        edits = param_edits(text, m, name, idx, len(ref))
        if edits:
            yield kind, f'{label_prefix}{name} param{idx} [{pp.strip()[:36]}]', apply_edits(text, edits)


def ret_sites(text, m, name):
    edits = []
    for ns, ps, pe in signatures(m, name):
        ls = max(m.rfind('\n', 0, ns), m.rfind(';', 0, ns), m.rfind('{', 0, ns), m.rfind('}', 0, ns)) + 1
        seg = m[ls:ns]
        seg2 = re.sub(r'(?:\w+::)+$', '', seg).rstrip()
        if not seg2.endswith(('*', '&')):
            return
        mm = re.match(r'(\s*(?:(?:static|inline|extern|virtual|DECOMP_\w+)\s+)*)(const\s+)?', seg2)
        a = ls + mm.end(1)
        if mm.group(2):
            edits.append((a, a + len(mm.group(2)), ''))
        else:
            edits.append((a, a, 'const '))
    if edits:
        yield 'ret', f'{name} return type', apply_edits(text, edits)


def method_sites(text, m, name):
    edits = []
    arity = None
    for ns, ps, pe in signatures(m, name):
        before = m[:ns].rstrip()
        if before.endswith('::') is False and enclosing(blocks_cache(m), ns) != 'type':
            continue
        n = len(split_params(text[ps:pe]))
        arity = arity or n
        if n != arity:
            continue
        tail = m[pe + 1:pe + 40]
        mm = re.match(r'(\s*)(const\b)?', tail)
        if mm.group(2):
            edits.append((pe + 1 + mm.start(1), pe + 1 + mm.end(2), ''))
        else:
            edits.append((pe + 1, pe + 1, ' const'))
    if edits:
        yield 'method', f'{name}() const', apply_edits(text, edits)


_EXTERN = re.compile(r'^([ \t]*extern\s+(?:"C(?:\+\+)?"\s+)?)(const\s+)?([A-Za-z_][\w:<>\s\*&,]*?)\s*\b(\w+)((?:\[[^\]]*\])*)\s*;', re.M)


def global_sites(text, m, bo, bc):
    """One site per file-level extern variable used in the body: toggle `const` on every extern declaration of it."""
    used = set(re.findall(r'(?<![\w.>])(\w+)\b(?!\s*\()', m[bo:bc]))
    by_name = {}
    for mm in _EXTERN.finditer(m):
        if '(' in mm.group(0) or mm.group(4) not in used or mm.group(4) in KEYWORDS:
            continue
        if enclosing(_BL, mm.start()) not in ('file', 'ns') or bo < mm.start() < bc:
            continue
        by_name.setdefault(mm.group(4), []).append(mm)
    for name, decls in by_name.items():
        remove = bool(decls[0].group(2))
        edits = []
        for mm in decls:
            if bool(mm.group(2)) != remove:
                break  # inconsistent constness among declarations: skip
            if remove:
                edits.append((mm.start(2), mm.end(2), ''))
            else:
                edits.append((mm.start(3), mm.start(3), 'const '))
        else:
            lines = ','.join(str(text.count('\n', 0, d.start()) + 1) for d in decls[:3])
            yield 'global', f'{"-" if remove else "+"}const {name} (decl line {lines})', apply_edits(text, edits)


_BL = []  # blocks of the file currently being analysed (set by gen_sites)


def blocks_cache(m):
    return _BL


def gen_sites(text, fn, kinds):
    m = mask(text)
    bl = blocks(m)
    _BL[:] = bl
    bd = body_of(m, bl, fn)
    if bd is None:
        return
    bo, bc = bd
    body = m[bo:bc]
    if 'param' in kinds:
        yield from param_sites(text, m, fn, 'param')
    if 'member' in kinds:
        names = set(re.findall(r'(?:->|\.)\s*(\w+)', body))
        pat = re.compile(r'^([ \t]+)(const\s+)?((?:unsigned\s+|struct\s+)?[A-Za-z_][\w:]*(?:<[^;>=()]*>)?)(\s*)([*&])(\s*)(\w+)((?:\[[^\]]*\])*)\s*;', re.M)
        for mm in pat.finditer(m):
            if mm.group(7) not in names or mm.group(3) in KEYWORDS or bo < mm.start() < bc:
                continue
            if enclosing(bl, mm.start()) != 'type':
                continue
            if mm.group(2):
                ed = [(mm.start(2), mm.end(2), '')]
            else:
                ed = [(mm.start(3), mm.start(3), 'const ')]
            line = text.count('\n', 0, mm.start()) + 1
            yield 'member', f'line{line} {mm.group(7)}', apply_edits(text, ed)
    if 'local' in kinds:
        pat = re.compile(r'^([ \t]*(?:for\s*\(\s*)?)(const\s+)?((?:unsigned\s+|signed\s+|struct\s+)?[A-Za-z_][\w:]*(?:<[^;>=]*>)?)(\s*)([*&])(\s*)(\w+)\s*=(?!=)', re.M)
        for mm in pat.finditer(m, bo, bc):
            if mm.group(3) in KEYWORDS:
                continue
            if mm.group(2):
                ed = [(mm.start(2), mm.end(2), '')]
            else:
                ed = [(mm.start(3), mm.start(3), 'const ')]
            line = text.count('\n', 0, mm.start()) + 1
            yield 'local', f'line{line} {mm.group(7)}', apply_edits(text, ed)
    called = []
    for nm in re.findall(r'(?<![\w.>])(\w+)\s*\(', body):
        if nm not in KEYWORDS and nm != fn and nm not in called:
            called.append(nm)
    mcalled = []
    for nm in re.findall(r'(?:->|\.)\s*(\w+)\s*\(', body):
        if nm not in mcalled:
            mcalled.append(nm)
    if 'helper' in kinds:
        for nm in called + [x for x in mcalled if x not in called]:
            yield from param_sites(text, m, nm, 'helper')
    if 'ret' in kinds:
        for nm in called + [x for x in mcalled if x not in called]:
            yield from ret_sites(text, m, nm)
    if 'method' in kinds:
        for nm in mcalled:
            yield from method_sites(text, m, nm)
    if 'global' in kinds:
        yield from global_sites(text, m, bo, bc)
    if 'cast' in kinds:
        for mm in re.finditer(r'\((const\s+)?([A-Za-z_][\w:]*)(\s*)\*(\s*)\)', body):
            if mm.group(2) in ('void',) and not mm.group(1):
                pass
            a = bo + mm.start()
            if mm.group(1):
                ed = [(a + 1, a + 1 + len(mm.group(1)), '')]
            else:
                ed = [(a + 1, a + 1, 'const ')]
            line = text.count('\n', 0, a) + 1
            yield 'cast', f'line{line} ({mm.group(2)}*)', apply_edits(text, ed)


# ---------------------------------------------------------------------------------------------

def sweep(shard, nshards, wt, cands_path, logdir, kinds, only, max_base, max_sites, deep):
    os.chdir(wt)
    subprocess.run(['git', 'checkout', '--', 'src'], capture_output=True)
    cands = [c for i, c in enumerate(json.load(open(cands_path))) if i % nshards == shard]
    if only:
        cands = [c for c in cands if any(o in c[0] or o == c[1] for o in only)]
    os.makedirs(logdir, exist_ok=True)
    log = open(os.path.join(logdir, f'shard{shard}.log'), 'a')
    res = open(os.path.join(logdir, f'results{shard}.jsonl'), 'a')

    def say(*a):
        print(*a, file=log, flush=True)

    def lines(unit, fn):
        obj = f'build/RZTE01_01/src/{unit}.o'
        if os.path.exists(obj):
            os.remove(obj)
        subprocess.run(['python3', 'tools/verify.py', unit], capture_output=True, text=True, timeout=900)
        if not os.path.exists(obj):
            return None
        r = subprocess.run(['python3', 'tools/asm_diff.py', unit, fn, '-n', '1'],
                           capture_output=True, text=True, timeout=900)
        mm = re.search(r'SUMMARY: \S+: (\d+) differing', r.stdout)
        return int(mm.group(1)) if mm else None

    for unit, fn, pct in cands:
        src = f'src/{unit}.cpp'
        if not os.path.exists(src):
            src = f'src/{unit}.c'
        if not os.path.exists(src):
            continue
        orig = open(src).read()
        base = lines(unit, fn)
        say(f'== {unit} {fn} base_lines={base}')
        if base is None or base == 0 or base > max_base:
            continue
        try:
            sites = list(gen_sites(orig, fn, kinds))
        except Exception as e:  # analysis bug: log and move on
            say(f'   site generation failed: {e!r}')
            continue
        seen, trials = {orig}, []
        for kind, label, new in sites:
            if new in seen:
                continue
            seen.add(new)
            trials.append((kind, label, new))
        say(f'   {len(trials)} sites' + (f' (capped to {max_sites})' if len(trials) > max_sites else ''))
        def measure(text, kind, label, ref_n):
            open(src, 'w').write(text)
            try:
                n = lines(unit, fn)
            except Exception:
                n = None
            finally:
                open(src, 'w').write(orig)
            say(f'   {kind:6} {label[:70]} -> {n}')
            res.write(json.dumps({'unit': unit, 'fn': fn, 'kind': kind, 'label': label,
                                  'base': ref_n, 'n': n}) + '\n')
            res.flush()
            return n

        cur_text, cur_n, chain = orig, base, []
        for rnd in range(1 + (deep if True else 0)):
            if rnd:
                trials, seen = [], {cur_text}
                for kind, label, new in gen_sites(cur_text, fn, kinds):
                    if new not in seen:
                        seen.add(new)
                        trials.append((kind, label, new))
                say(f'   round {rnd}: {len(trials)} sites from current best ({cur_n})')
            best = (cur_n, None, None)
            for kind, label, new in trials[:max_sites]:
                n = measure(new, kind, label, cur_n)
                if n is not None and n < best[0]:
                    best = (n, f'{kind} {label}', new)
            if best[1] is None:
                break
            cur_n, cur_text = best[0], best[2]
            chain.append(best[1])
        if chain:
            say(f'** GAIN {unit} {fn} {base} -> {cur_n} via ' + ' + '.join(chain))
            if deep:
                open(src, 'w').write(cur_text)
                d = subprocess.run(['git', 'diff', '--', src], capture_output=True, text=True).stdout
                open(src, 'w').write(orig)
                open(os.path.join(logdir, f'patch_{fn}.diff'), 'w').write(d)
    say('DONE')


def rank(logdir):
    rows = []
    for f in sorted(os.listdir(logdir)):
        if f.startswith('results') and f.endswith('.jsonl'):
            for line in open(os.path.join(logdir, f)):
                r = json.loads(line)
                if r['n'] is not None and r['n'] < r['base']:
                    rows.append(r)
    rows.sort(key=lambda r: (r['n'], -(r['base'] - r['n'])))
    for r in rows:
        print(f"{r['unit'].split('/')[-1]:28} {r['fn']:12} {r['kind']:6} {r['label'][:48]:48} {r['base']} -> {r['n']}")
    print(len(rows), 'improvements')


def main(argv):
    if argv and argv[0] == '--make-cands':
        opts = dict(zip(argv[2::2], argv[3::2]))
        make_cands(argv[1], float(opts.get('--min', 96)), int(opts.get('--max-size', 3500)))
        return
    if argv and argv[0] == '--rank':
        rank(argv[1])
        return
    if len(argv) < 3:
        print(__doc__)
        sys.exit(1)
    opts = dict(zip(argv[3::2], argv[4::2]))
    kinds = opts.get('--kinds', ','.join(KINDS_DEFAULT)).split(',')
    only = [o for o in opts.get('--only', '').split(',') if o]
    sweep(int(argv[0]), int(argv[1]), argv[2], opts.get('--cands', 'cands.json'),
          opts.get('--logdir', '/tmp/cs'), kinds, only, int(opts.get('--max-base', 150)),
          int(opts.get('--max-sites', 80)), int(opts.get('--deep', 0)))


if __name__ == '__main__':
    main(sys.argv[1:])
