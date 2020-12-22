#include "performance.h"

#if defined(BM_WINDOWS)
#include <Windows.h>
#else
#include <SDL.h>
#define SDL_PERF
#endif

static inline u64 get_clock_freq(void) {
#if defined(SDL_PERF)
    const u64 freq = SDL_GetPerformanceFrequency();
#elif defined(BM_WINDOWS)
    LARGE_INTEGER clock_freq = { 0 };
    QueryPerformanceFrequency(&clock_freq);
    const u64 freq = clock_freq.QuadPart;
#endif
    return freq;
}

f64 perf_seconds(void) {
#if defined(SDL_PERF)
    const f64 seconds = (f64)SDL_GetPerformanceCounter() /
        (f64)get_clock_freq();
#elif defined(BM_WINDOWS)
    LARGE_INTEGER qpc_value = { 0 };
    qpc_value.QuadPart = 0LL;

    QueryPerformanceCounter(&qpc_value);

    const f64 seconds = (f64)((f64)(qpc_value.QuadPart) / (f64)(get_clock_freq()));
#endif
    return seconds;
}

u64 perf_microseconds(void) {
    return (u64)(perf_seconds() * 1000000ULL);
}

f64 perf_milliseconds(void) {
    return (f64)((f64)(perf_microseconds()) / 1000.0);
}
