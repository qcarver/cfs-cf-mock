// filepath: /cfs-cf-mock/cfs-cf-mock/include/cfe/cfe_evs.h
#ifndef CFE_EVS_H
#define CFE_EVS_H

#include <stdint.h>

CFE_Status_t CFE_EVS_SendEvent(uint16 EventID, CFE_EVS_EventType_Enum_t EventType, const char *Spec, ...);

CFE_Status_t CFE_EVS_Register(const void *Filters, uint16 NumEventFilters, uint16 FilterScheme);

#endif // CFE_EVS_H