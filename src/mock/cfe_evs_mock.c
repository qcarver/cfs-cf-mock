#include "cfe_evs_mock.h"

void CFE_EVS_SendEvent(uint32 EventID, uint32 EventType, const char *Spec, ...)
{
    // Mock implementation: Simulate sending an event
}

void CFE_EVS_Register(void *DataPtr, uint16 EventID, uint16 EventType)
{
    // Mock implementation: Simulate registering for events
}

void CFE_EVS_Unregister(uint32 AppId)
{
    // Mock implementation: Simulate unregistering from events
}

void CFE_EVS_SendEventWithAppID(uint32 EventID, uint32 EventType, uint32 AppId, const char *Spec, ...)
{
    // Mock implementation: Simulate sending an event with App ID
}