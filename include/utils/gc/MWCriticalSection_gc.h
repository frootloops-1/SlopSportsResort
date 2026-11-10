#ifndef UTILS_GC_MWCRITICALSECTION_GC_H
#define UTILS_GC_MWCRITICALSECTION_GC_H

#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

void MWInitializeCriticalSection(u32* section);
void MWEnterCriticalSection(u32* section);
void MWExitCriticalSection(u32* section);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_GC_MWCRITICALSECTION_GC_H */
