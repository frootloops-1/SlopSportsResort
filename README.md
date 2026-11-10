Wii Sports Resort
=================

A work-in-progress matching decompilation of **Wii Sports Resort** (Nintendo, 2009) for the Wii.

The goal is C/C++ source that, built with the original Metrowerks CodeWarrior compilers, produces a `main.dol`
byte-identical to the retail one.

Supported version:

- `RZTE01_01`: USA, disc revision 1

> [!IMPORTANT]
> **AI disclaimer.** This decompilation is being done entirely by AI. The C/C++ source, symbol and split
> recovery, tooling and documentation in this repository were written by AI coding agents (Anthropic's Claude
> models, via Claude Code), with a human only steering the work and reviewing results. Expect the code, names and
> comments to carry the mistakes an AI can make: guessed names, wrong types, misleading comments.
>
> What keeps it honest is the build: a unit only counts as "Matching" when its compiled object is byte-identical to
> the original and the whole DOL still links to the retail hash. Function names that aren't backed by strings, RTTI,
> vtables or a matched counterpart stay as placeholders (`fn_XXXXXXXX`, `Unk_<addr>`). Treat everything else (docs,
> comments, the "lessons" notes) as unverified AI-written notes, not authoritative research.

This repository does **not** contain any game assets, disc images, executables or assembly. You need your own
legally obtained copy of the game to build it.

Status
======

Early days. Most of what matches so far is library code (NintendoWare, EGG, the Revolution SDK, MSL) shared with
Wii Sports; game code is largely still unsplit. Run `ninja progress` after a build for current numbers.

- [`docs/decompilation-roadmap.md`](docs/decompilation-roadmap.md): phases and how targets are picked
- [`docs/milestones.md`](docs/milestones.md): project milestones
- [`AGENTS.md`](AGENTS.md): the working instructions the AI agents follow

Much of the shared library and framework code was ported from the Wii Sports decompilation. Thanks to everyone
behind [decomp-toolkit](https://github.com/encounter/decomp-toolkit), [objdiff](https://github.com/encounter/objdiff)
and the wider GC/Wii decompilation community, whose tools and prior work this builds on.

Dependencies
============

Windows
-------

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%` (or `pip install ninja`).

macOS
-----

```sh
brew install ninja
```

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, is downloaded and used
automatically to run the compilers.

Linux
-----

Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages). wibo is used automatically, as
on macOS.

Building
========

1. Clone the repository.
2. Copy your disc image of the game into `orig/RZTE01_01/`.
   - Supported formats: ISO (GCM), RVZ, WIA, WBFS, CISO, NFS, GCZ, TGC.
   - After the first build the disc image can be deleted to save space.
3. Configure and build:

   ```sh
   python configure.py
   ninja
   ```

   A successful build ends with `build/RZTE01_01/main.dol: OK`.

Diffing
=======

After the first build an `objdiff.json` exists in the project root. Open the project directory in
[objdiff](https://github.com/encounter/objdiff) and pick an object from the sidebar; it rebuilds automatically when
sources, headers, `configure.py`, `splits.txt` or `symbols.txt` change.

Legal
=====

This is an unofficial fan project, not affiliated with or endorsed by Nintendo. *Wii Sports Resort* and *Wii* are
trademarks of Nintendo. No copyrighted game data is distributed here.
