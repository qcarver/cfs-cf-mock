// filepath: /cfs-cf-mock/cfs-cf-mock/include/mock/cfe_evs_mock.h
#ifndef CFE_EVS_MOCK_H
#define CFE_EVS_MOCK_H

#ifdef __cplusplus
extern "C" {
#endif

void CFE_EVS_SendEvent(uint32 EventID, uint32 EventType, const char *Spec, ...);
void CFE_EVS_Register(void *DataPtr, uint32 EventID, uint32 EventType);
void CFE_EVS_Unregister(void);
void CFE_EVS_ResetAllCounters(void);
void CFE_EVS_GetEventQueue(void);

#ifdef __cplusplus
}
#endif

#endif // CFE_EVS_MOCK_H