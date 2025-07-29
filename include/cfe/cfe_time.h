// filepath: /cfs-cf-mock/cfs-cf-mock/include/cfe/cfe_time.h
#ifndef CFE_TIME_H
#define CFE_TIME_H

#include <stdint.h>

typedef struct
{
    uint32_t Seconds;
    uint32_t Microseconds;
} CFE_TIME_SysTime_t;

CFE_TIME_SysTime_t CFE_TIME_GetTime(void);
void CFE_TIME_SetTime(CFE_TIME_SysTime_t time);
void CFE_TIME_GetCurrentTime(CFE_TIME_SysTime_t *time);
void CFE_TIME_IncrementTime(uint32_t increment);

#endif // CFE_TIME_H