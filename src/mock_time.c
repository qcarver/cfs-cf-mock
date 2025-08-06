#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "cfe/cfe_time.h"

// Mock implementation of CFE Time Services (TIME) functions

CFE_TIME_SysTime_t CFE_TIME_GetTime(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    CFE_TIME_SysTime_t sysTime;
    sysTime.Seconds = ts.tv_sec;
    sysTime.Subseconds = (uint32)((((uint64)ts.tv_nsec) << 32) / 1000000000);  // Convert nsec to cFS-style subseconds
    return sysTime;
}
