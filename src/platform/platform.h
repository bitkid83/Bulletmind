#pragma once

#include "types.h"
#include "platform/export.h"

#ifdef __cplusplus
extern "C"
#endif

BM_PLATFORM_EXPORT void os_sleep_ms(const u32 duration);
BM_PLATFORM_EXPORT u64 os_get_time_ns(void);



