# Reverse-engineering notes

## Source status

The working `.c` files are decompiler outputs of the current modified binaries:

- `Gamex86.dll`
- `Wolf2.exe`

They are not the original game source project. The complete decompiler outputs are deliberately excluded from this package.

## 1. Confirmed AI-limit modification

Current `Gamex86.dll` contains a tiny function at virtual address `0x20001061` whose effective operation is:

```c
*(uint32_t *)(ESI + 0x31C) = 999999;
```

That value is unusually distinctive and matches the mod's global-AI-limit work. A clean symbolic reconstruction is provided in `patches/gamex86_patches.c`.

A nearby/related engine path also parses the key/name `maxActiveAI`. More type and cross-reference recovery is needed before assigning a definitive class member name to `+0x31C`.

## 2. LipSync overlap path

The current `Gamex86.dll` contains the diagnostic string:

`LipSync("%s"): is in use, will fail to play...`

In the currently decompiled control flow, after the in-use check and diagnostic call, execution continues into subsequent lipsync setup/processing in the same path instead of showing an immediate return at that point.

This is **consistent with** the modified build allowing overlapping voice/lipsync activity, but it is marked as likely modified behavior until compared byte-for-byte/control-flow-for-control-flow with a clean DLL.

## 3. Havok thread-selection path

`Wolf2.exe` function around VA `0x10042530` references `hk_numThreads` and selects an observed value of either `1` or `2` depending on engine/system conditions.

This is a useful target for anyone investigating:

- CPU/core behavior
- Havok worker configuration
- VR frame pacing
- configurable thread-count experiments

The `Gamex86.dll` initialization path also queries `hk_numThreads` and changes internal values when the result is below `2`.

## 4. Occlusion-culling path

The current `Wolf2.exe` contains a setup path that accesses:

- `r_occlusionCullMasterEnable`
- `r_occlusionCullDynamicModels`
- `r_occlusionCullPortals`

These names are grouped closely in the decompiled control flow and are useful renderer/visibility research anchors for a VR mod.

The current inspection proves the cvar access path exists; it does not by itself prove that the access code is a custom patch.

## 5. Havok entity/debris removal

The executable contains the diagnostic paths:

- `idCollisionModelManagerHavok::hkRemoveEntity: warning, removal of hkEnt ... delayed!`
- `idCollisionModelManagerHavok::hkRemoveEntity: removing batch debris from queue ...`

These are useful locations when investigating crashes or stalls caused by large amounts of physics debris/effects.

## 6. What to compare next

For a precise public patch set, the strongest next step is to decompile a clean, unmodified copy of the same game version with the same decompiler settings and compare functions by virtual address.

That would let us classify each change as:

1. exact byte/value patch,
2. altered branch/condition,
3. injected helper/trampoline,
4. unchanged original engine code.

Once that baseline exists, additional reconstructed patch files can be added without publishing the complete original-derived decompilation.
