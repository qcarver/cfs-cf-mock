#ifndef CFE_TIME_MOCK_H
#define CFE_TIME_MOCK_H

#include <stdint.h>
#include <stdbool.h>

// Mock function declarations for CFE Time Services

void CFE_TIME_SetTime(uint32_t seconds, uint32_t microseconds);
void CFE_TIME_GetTime(uint32_t *seconds, uint32_t *microseconds);
bool CFE_TIME_Compare(uint32_t time1_seconds, uint32_t time1_microseconds,
                       uint32_t time2_seconds, uint32_t time2_microseconds);
void CFE_TIME_GetCurrentTime(uint32_t *seconds, uint32_t *microseconds);

#endif // CFE_TIME_MOCK_H