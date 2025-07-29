#include "cfe_time_mock.h"

void CFE_TIME_GetTime(CFE_TIME_SysTime_t *Time) {
    // Mock implementation: Set time to a fixed value
    Time->Seconds = 1234567890; // Example fixed time
    Time->Subseconds = 0; // Example fixed subseconds
}

void CFE_TIME_SetTime(CFE_TIME_SysTime_t Time) {
    // Mock implementation: Do nothing
}

void CFE_TIME_GetTimeOfDay(CFE_TIME_SysTime_t *Time) {
    // Mock implementation: Set time of day to a fixed value
    Time->Seconds = 1234567890; // Example fixed time
    Time->Subseconds = 0; // Example fixed subseconds
}

void CFE_TIME_SetTimeOfDay(CFE_TIME_SysTime_t Time) {
    // Mock implementation: Do nothing
}

void CFE_TIME_GetElapsedTime(CFE_TIME_SysTime_t StartTime, CFE_TIME_SysTime_t EndTime, CFE_TIME_SysTime_t *ElapsedTime) {
    // Mock implementation: Calculate elapsed time
    ElapsedTime->Seconds = EndTime.Seconds - StartTime.Seconds;
    ElapsedTime->Subseconds = EndTime.Subseconds - StartTime.Subseconds;
    if (ElapsedTime->Subseconds < 0) {
        ElapsedTime->Seconds -= 1;
        ElapsedTime->Subseconds += 1000000; // Assuming 1 second = 1,000,000 subseconds
    }
}