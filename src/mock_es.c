#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>  // Add this for va_list, va_start, va_end
#include "cfe/cfe_es.h"
#include "cfe/cfe_error.h"

// Mock implementation of CFE Executive Services (ES) functions

//declared in main, is "1" until Ctrl-C or ExitApp
extern volatile uint32_t AppRunStatus;

//looking for PerfLogEntry or PerfLogExit? see .h

void CFE_ES_PerfLogAdd(uint32 Marker, uint32 EntryExit)
{
    // Delegate mock WriteToSysLog for consstentancy
    CFE_ES_WriteToSysLog("PerfLog: Marker=%u, EntryExit=%u", Marker, EntryExit);
}

CFE_Status_t CFE_ES_WriteToSysLog(const char *SpecStringPtr, ...)
{
    bool fail = false;
    va_list args;
    va_start(args, SpecStringPtr);
    fail = vprintf(SpecStringPtr, args) < 0;
    printf("\n");
    va_end(args);
    // Maybe a bad error spoof, but atleast its one possible failure mode
    return (fail) ? CFE_ES_ERR_SYS_LOG_FULL :  CFE_SUCCESS;
}

bool CFE_ES_RunLoop(uint32 *RunStatus)
{
    // Mock skeleton implementation
    return AppRunStatus != 0;
}

void CFE_ES_ExitApp(uint32 ExitStatus)
{
    AppRunStatus = 0;
}

CFE_Status_t CFE_ES_GetAppID(CFE_ES_AppId_t *AppIdPtr)
{
    // Mock skeleton implementation
    return CFE_SUCCESS;
}
