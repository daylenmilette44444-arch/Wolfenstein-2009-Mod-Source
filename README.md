# Wolfenstein 2009 Mod – Reverse Engineering Notes

This repository contains **original patch notes and small reconstruction helpers** derived from reverse-engineering my modified Wolfenstein (2009) build.

It intentionally does **not** include the complete decompiled `Wolf2.exe` or `Gamex86.dll` source, and it does not include original game binaries or assets.

## What is included

- `patches/gamex86_patches.c` – small reconstructed helper for a confirmed AI-limit modification.
- `patches/wolf2_re_notes.c` – symbolic notes for useful engine locations found in the current EXE decompilation.
- `docs/reverse_engineering_notes.md` – technical observations for developers who want to continue research, including VR-mod work.

## Important status note

The available `.c` files are full decompiler outputs, not the original Raven/id source tree. Because only the current modified build is being inspected here, not every difference can be proven to be a custom patch without comparing against a clean/original build.

Items are therefore marked as:

- **Confirmed modification** – the current decompilation contains a very distinctive modification that matches the mod behavior/history.
- **Observed engine location** – useful function/cvar location, but not claimed as an original custom patch by itself.
- **Likely modified behavior** – current control flow is consistent with the mod behavior, but a clean binary comparison is still needed for proof.

## Confirmed modification

### Global AI / spawner limit

In the current `Gamex86.dll` decompilation, function VA `0x20001061` writes decimal `999999` to `ESI + 0x31C`.

This is preserved in `patches/gamex86_patches.c` as a small reconstruction rather than publishing the complete decompiled DLL.

## Useful engine locations

The current EXE/DLL decompilations also expose:

- `hk_numThreads` initialization / lookup paths.
- `r_occlusionCullMasterEnable` and related occlusion-culling cvars.
- The `LipSync("%s"): is in use...` path in `Gamex86.dll`.
- Havok `hkRemoveEntity` / batch-debris removal paths.

These are documented as research targets rather than redistributed decompiled source.

## VR modding

Forking these notes and original helper code for a Wolfenstein (2009) VR project is welcome. Please credit the original mod/research work when reusing it.

## Legal / project scope

Wolfenstein (2009), its original executable, DLLs, assets, trademarks, and original code remain the property of their respective rights holders. This repository is an independent modding/reverse-engineering project and is not affiliated with or endorsed by the original developers or publishers.
