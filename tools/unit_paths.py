#!/usr/bin/env python3
"""Canonical unit paths: the ogws (Wii Sports) src layout.

Split names ported from other projects (forecast, zeldaret/ss, mkw, dtk auto names) use other
directory spellings. On a case-insensitive filesystem `revolution/os` and `revolution/OS` are one
directory, so every unit path goes through canonical() before it lands in splits.txt.

  unit_paths.py [SPLITS] [--apply]   # list (or apply) renames in a splits.txt
"""
import re, sys

# Directory renames, first match wins (prefix -> replacement).
DIRS = [
    ('TRK_MINNOW_DOLPHIN/debugger/embedded/MetroTRK/', 'MetroTRK/debugger/'),
    ('TRK_MINNOW_DOLPHIN/gamedev/cust_connection/cc/exi2/GCN/EXI2_GDEV_GCN/', 'MetroTRK/gamedev/'),
    ('MetroTRK/debugger/embedded/MetroTRK/Processor/ppc/Generic/', 'MetroTRK/debugger/Processor/'),
    ('MetroTRK/debugger/embedded/MetroTRK/', 'MetroTRK/debugger/'),
    ('Runtime.PPCEABI.H/', 'runtime/'),
    ('MSL_C/', 'MSL/'),
    ('MSL/src/', 'MSL/'),
    ('rfl/', 'RVLFaceLib/'),
    ('rvl/axfx/', 'revolution/AXFX/'),
    ('revolution/HBM/', 'homebuttonMiniLib/'),
    ('hbm/homebutton/', 'homebuttonMiniLib/'),
    ('hbm/', 'homebuttonMiniLib/'),
    ('revolution/bte/btm_', 'revolution/BTE/stack/btm/btm_'),
    ('revolution/bte/uusb_', 'revolution/BTE/rvl/uusb_'),
]
# revolution/<lib>/: ogws spells every SDK library directory in upper case.
SDK_UPPER = {'os', 'gx', 'mem', 'mtx', 'sc', 'usb', 'arc', 'ax', 'axfx', 'base', 'dvd', 'tpl',
             'wpad', 'kpad', 'nand', 'fs', 'esp', 'vi', 'si', 'exi', 'ai', 'dsp', 'db', 'ipc',
             'pad', 'cnt', 'net', 'wud', 'euart', 'wenc', 'vf', 'bte'}
# Whole-file renames: dtk/mkw object names and other projects' file names -> ogws names.
# Each is backed by the functions in the unit (see docs/symbol_recovery.md).
FILES = {
    'unconfigured/fs.o': 'revolution/FS/fs.c',
    'unconfigured/esp.o': 'revolution/ESP/esp.c',
    'unconfigured/gxBump.o': 'revolution/GX/GXBump.c',
    'unconfigured/gxTransform.o': 'revolution/GX/GXTransform.c',
    'unconfigured/osThread.o': 'revolution/OS/OSThread.c',
    'unconfigured/rvlNand1.o': 'revolution/NAND/nand.c',           # NANDRead/Write/Seek/Delete/Move
    'rvl/axfx/rvlAxFxReverbHiExp.c': 'revolution/AXFX/AXFXReverbHiExp.c',
    'rvl/mem/rvlMemExpHeap.c': 'revolution/MEM/mem_expHeap.c',          # MEMCreateExpHeapEx...
    'rvl/mem/rvlMemAllocator.cpp': 'revolution/MEM/mem_allocator.c',    # unmangled MEMAllocFromAllocator
    'rvl/mtx/rvlQuat.c': 'revolution/MTX/quat.c',
    'nw4r/snd/snd_dvdSoundArchive.cpp': 'nw4r/snd/snd_DvdSoundArchive.cpp',   # mkw spelling
    'unconfigured/dvdBroadway.o': 'revolution/DVD/dvd_broadway.c',      # DVDLowInit/DVDLowOpenPartition
    'MSL/src/wchar.c': 'MSL/wstring.c',                              # wcslen/wcscpy/wcsncpy/wcscmp
    'rfl/rfl_init.c': 'RVLFaceLib/RFL_System.c',                     # RFLGetWorkSize/RFLInitResAsync
    'Runtime.PPCEABI.H/Gecko_ExceptionPPC.cpp': 'runtime/Gecko_ExceptionPPC.c',
    # hbm/sound/*.cpp stay C++: synsample has mangled names (__HBMSYNSetupAdpcm__FP11HBMSYNVOICE).
}


def canonical(path):
    if path in FILES:
        return FILES[path]
    for old, new in DIRS:
        if path.startswith(old):
            path = new + path[len(old):]
            break
    path = re.sub(r'/rvlAxFx(\w+\.c)$', r'/AXFX\1', path)            # mkw spelling of AXFX files
    m = re.match(r'revolution/([^/]+)/(.*)', path)
    if m and m[1].lower() in SDK_UPPER:
        lib = m[1].upper() if m[1].lower() != 'vf' else 'VF'
        path = f'revolution/{lib}/{m[2]}'
    return path


def rename_splits(text):
    """Return (new_text, [(old, new)]) with unit header lines rewritten."""
    out, ren = [], []
    for line in text.splitlines(keepends=True):
        m = re.match(r'^([^\s].*?):(.*)$', line.rstrip('\n'))
        if m and m[1] != 'Sections':
            new = canonical(m[1])
            if new != m[1]:
                ren.append((m[1], new))
                line = f'{new}:{m[2]}\n'
        out.append(line)
    return ''.join(out), ren


if __name__ == '__main__':
    args = [a for a in sys.argv[1:] if a != '--apply']
    path = args[0] if args else 'config/RZTE01_01/splits.txt'
    text = open(path).read()
    new, ren = rename_splits(text)
    units = [l.split(':')[0] for l in new.splitlines() if l[:1] not in ('', ' ', '\t') and ':' in l]
    dup = {u for u in units if units.count(u) > 1}
    for o, n in ren:
        print(f'{o} -> {n}')
    print(f'{len(ren)} renames')
    if dup:
        sys.exit(f'duplicate unit names after rename: {sorted(dup)}')
    if '--apply' in sys.argv:
        open(path, 'w').write(new)
