/*
 * Wolfenstein (2009) - Gamex86 patch reconstruction
 *
 * This file contains only a small reconstruction of a confirmed modification
 * visible in the current modified Gamex86.dll decompilation. It is NOT the
 * original Gamex86 source code and does not contain the full decompiler output.
 */

#include <stdint.h>
#include <stddef.h>

/*
 * Confirmed in current modified build:
 *   VA: 0x20001061
 *   Decompiled operation:
 *       *(uint32_t *)(ESI + 0x31C) = 999999;
 *
 * The exact class/type represented by ESI should be renamed after additional
 * type recovery. The symbolic helper below preserves only the patch behavior.
 */
#define WOLF_AI_LIMIT_FIELD_OFFSET 0x31Cu
#define WOLF_AI_LIMIT_PATCH_VALUE  999999u

void wolf_patch_global_ai_limit(void *object_base)
{
    if (object_base == NULL) {
        return;
    }

    *(uint32_t *)((uint8_t *)object_base + WOLF_AI_LIMIT_FIELD_OFFSET) =
        WOLF_AI_LIMIT_PATCH_VALUE;
}

/*
 * Related observed engine path:
 * Gamex86 also reads the spawn key/cvar-style field named "maxActiveAI".
 * Do not assume the +0x31C field is fully typed until a clean-build comparison
 * and additional cross-reference analysis are completed.
 */
