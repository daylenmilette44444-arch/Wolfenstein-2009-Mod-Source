/*
 * Wolfenstein (2009) - Wolf2.exe reverse-engineering symbols
 *
 * These are research notes expressed as C constants. They are NOT a copy of
 * the complete decompiled executable and are not all claimed to be custom
 * patches.
 */

#include <stdint.h>

/* Observed cvar names in the current executable. */
static const char WOLF_CVAR_HK_NUM_THREADS[] = "hk_numThreads";
static const char WOLF_CVAR_OCCLUSION_MASTER[] = "r_occlusionCullMasterEnable";
static const char WOLF_CVAR_OCCLUSION_DYNAMIC[] = "r_occlusionCullDynamicModels";
static const char WOLF_CVAR_OCCLUSION_PORTALS[] = "r_occlusionCullPortals";

/*
 * Observed hk_numThreads initialization behavior near function 0x10042530:
 * the engine chooses between values 1 and 2 depending on detected conditions.
 * This is useful for locating the thread-selection path when implementing a
 * cleaner configurable or VR-oriented patch.
 */
enum wolf_observed_havok_thread_defaults {
    WOLF_HK_THREADS_LOW = 1,
    WOLF_HK_THREADS_HIGH = 2
};

/*
 * r_occlusionCullMasterEnable is queried in the current executable near the
 * map/controller setup path. Related dynamic-model and portal cvars are read
 * immediately afterwards. This is a useful hook/reference point for renderer
 * experiments, but this file does not claim that lookup itself is a custom
 * modification.
 */
