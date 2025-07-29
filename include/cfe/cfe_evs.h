// filepath: /cfs-cf-mock/cfs-cf-mock/include/cfe/cfe_evs.h
#ifndef CFE_EVS_H
#define CFE_EVS_H

#include <stdint.h>

#define CFE_EVS_MAX_MESSAGE_LENGTH 255

typedef struct {
    uint32_t EventID;
    char Message[CFE_EVS_MAX_MESSAGE_LENGTH];
} CFE_EVS_Event_t;

void CFE_EVS_SendEvent(uint32_t EventID, uint16_t EventType, const char *Spec, ...);
void CFE_EVS_Register(void *AppId, uint32_t EventFilter, uint32_t EventFilterSize);
void CFE_EVS_Unregister(void *AppId);
void CFE_EVS_SendEventWithAppID(uint32_t EventID, uint16_t EventType, const char *Spec, void *AppId, ...);

#endif // CFE_EVS_H