// filepath: /cfs-cf-mock/cfs-cf-mock/include/cfe/cfe_evs.h
#ifndef CFE_EVS_H
#define CFE_EVS_H

#include "common_types.h" 

/**
 * @brief Binary event filtering scheme
 */
#define CFE_EVS_EventFilter_BINARY 0

/**
 * @brief Event message filter definition structure
 */
typedef struct CFE_EVS_BinFilter
{
    uint16 EventID; /**< @brief Numerical event identifier */
    uint16 Mask;    /**< @brief Binary filter mask value */

} CFE_EVS_BinFilter_t;

enum CFE_EVS_EventType
{
    CFE_EVS_EventType_DEBUG = 1,        // Debug messages
    CFE_EVS_EventType_INFORMATION = 2,  // Status/informational messages
    CFE_EVS_EventType_ERROR = 3,        // Non-critical errors
    CFE_EVS_EventType_CRITICAL = 4      // Critical/irrecoverable errors
};

/**
 * @brief Mock initialization function - call before using EVS mock functionality
 */
void mock_evs_init(void);

/**
 * @brief Send an event message with specified ID, type, and format string
 *
 * This routine generates a software event message. If the EventID is not filtered,
 * the event will be sent as a software bus message. Uses printf-style formatting
 * with a limit of approximately 80 characters.
 *
 * @param[in] EventID   Numeric identifier for the event
 * @param[in] EventType Event classification (DEBUG, INFORMATION, ERROR, CRITICAL)
 * @param[in] Spec      Printf-style format string for the event message
 * @param[in] ...       Optional parameters for format string
 * @return CFE_SUCCESS on success, error code on failure
 */
CFE_Status_t CFE_EVS_SendEvent(uint16 EventID, CFE_EVS_EventType_Enum_t EventType, const char *Spec, ...);

/**
 * @brief Register application for event services with optional binary filters
 *
 * This routine registers an application with event services and allocates internal
 * data structures. Applications may not send events unless registered. Each call
 * overwrites all previously registered filters.
 *
 * @param[in] Filters         Pointer to array of event filters, or NULL if no filtering
 * @param[in] NumEventFilters Number of event filters in the array
 * @param[in] FilterScheme    Event filtering scheme (currently only binary supported)
 * @return CFE_SUCCESS on success, error code on failure
 */
CFE_Status_t CFE_EVS_Register(const void *Filters, uint16 NumEventFilters, uint16 FilterScheme);

#endif // CFE_EVS_H