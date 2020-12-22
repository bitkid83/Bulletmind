#pragma once

#include "types.h"

static inline f32 nsec_to_sec(const u64 nanos)
{
    return (f32)((f32)(nanos) / (f32)(1e-9));
}

static inline f32 nsec_to_msec(const u64 nanos)
{
    return (f32)((f32)(nanos) / (f32)(1e+6));
}

static inline f32 nsec_to_usec(const u64 nanos)
{
    return (f32)(nanos / 1000);
}
