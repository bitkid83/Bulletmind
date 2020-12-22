#pragma once

#include <Windows.h>

#include "platform/platform.h"

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

struct win_version_info {
	i32 major;
	i32 minor;
	i32 build;
	i32 revision;
};

static LARGE_INTEGER clock_freq;
static bool clock_initialized = false;
static u32 g_win_ver;

static inline u32 get_win_ver(void)
{
    if (g_win_ver == 0) {
        struct win_version_info win_ver;
        get_win_ver(&win_ver);
        g_win_ver = (win_ver.major << 8) | win_ver.minor;
    }
    return g_win_ver;
}

static inline u64 get_clock_freq(void)
{
    if (!clock_initialized) {
        QueryPerformanceFrequency(&clock_freq);
        clock_initialized = true;
    }
    return clock_freq.QuadPart;
}

void os_sleep_ms(const u32 duration)
{
    u32 d = duration;
    if (get_win_ver() >= 0x0602 & duration > 0)
        d--;
    Sleep(d);
}

u64 os_get_time_ns(void)
{
    LARGE_INTEGER current_time;
    f64 time_val = 0.0;

    QueryPerformanceCounter(&current_time);
    time_val = (f64)current_time.QuadPart;
    time_val *= 1000000000.0;
	time_val /= (f64)get_clock_freq();

	return (u64)time_val;
}
