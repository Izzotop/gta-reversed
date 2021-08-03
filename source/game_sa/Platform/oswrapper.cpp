#include "StdInc.h"

#include "oswrapper.h"

#include <Windows.h>

// 0x5617A0
uint64_t GetOSWPerformanceTime() {
    LARGE_INTEGER PerformanceCount = { 0 };
    ::QueryPerformanceCounter(&PerformanceCount);
    return PerformanceCount.QuadPart;
}

int64_t GetOSWPerformanceFrequency() {
    LARGE_INTEGER frequency;
    ::QueryPerformanceFrequency(&frequency);
    return frequency.QuadPart;
}