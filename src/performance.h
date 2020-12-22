#ifndef _H_TIMING
#define _H_TIMING

#include "c99defs.h"
#include "types.h"

u64 perf_microseconds(void);
f64 perf_seconds(void);
f64 perf_milliseconds(void);

#endif