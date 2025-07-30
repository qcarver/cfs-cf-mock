// filepath: /cfs-cf-mock/cfs-cf-mock/include/cfe/cfe_evs.h
#ifndef CFE_EVS_H
#define CFE_EVS_H

#include <stdint.h>

/** 
 ** \brief Mock initialization function - call before using EVS mock functionality 
 **/
void mock_evs_init(void);

/**
** \brief Generate a software event.
**
** \par Description
**          This routine generates a software event message.  If the EventID is not filtered,
**          the event will be sent as a software bus message, optionally logged in the local
**          event log, and optionally sent as an ASCII text string out the enabled output port(s).
**
** \par Assumptions, External Events, and Notes:
**          This API only works within the context of a registered application or core service.
**          For messages outside the context of a registered application (for example early
**          in app initialization or if registration fails) #CFE_ES_WriteToSysLog can be used
**          for reporting.
**
** \param[in] EventID            A numeric literal used to uniquely identify an application event.
**                               The \c EventID is defined and supplied by the application sending the event.
**
** \param[in] EventType          A numeric literal used to classify an event, one of:
**                                   \arg #CFE_EVS_EventType_DEBUG
**                                   \arg #CFE_EVS_EventType_INFORMATION
**                                   \arg #CFE_EVS_EventType_ERROR
**                                   \arg #CFE_EVS_EventType_CRITICAL
**
** \param[in] Spec               A pointer to a null terminated text string @nonnull describing the output format
**                               for the event.  This is the same type of format string used for the ANSI
**                               \c printf function.  Nominally the post-conversion string is limited to 80
**                               characters, but this limit is configurable through the parameter
**                               #CFE_MISSION_EVS_MAX_MESSAGE_LENGTH.  Characters beyond the limit will be truncated.
**                               Do not use floating point conversions (%f, %e, %E, %g, and %G) in the format
**                               string unless your application will be running in a system that supports
**                               floating point arithmetic.  Do not use non-printable characters (\\t, \\n, etc.)
**                               in the format string; they will mess up the formatting when the events are
**                               displayed on the ground system.
**
** \return Execution status, see \ref CFEReturnCodes
** \retval #CFE_SUCCESS                \copybrief CFE_SUCCESS
** \retval #CFE_EVS_APP_NOT_REGISTERED \copybrief CFE_EVS_APP_NOT_REGISTERED
** \retval #CFE_EVS_APP_ILLEGAL_APP_ID \copybrief CFE_EVS_APP_ILLEGAL_APP_ID
** \retval #CFE_EVS_INVALID_PARAMETER  \copybrief CFE_EVS_INVALID_PARAMETER
**
** \sa #CFE_EVS_SendEventWithAppID, #CFE_EVS_SendTimedEvent
**
**/

CFE_Status_t CFE_EVS_SendEvent(uint16 EventID, CFE_EVS_EventType_Enum_t EventType, const char *Spec, ...);

/**
** \brief Register an application for receiving event services
**
** \par Description
**          This routine registers an application with event services and allocates/initializes
**          the internal data structures used to support this application's events.  An application
**          may not send events unless it has called this routine.  The routine also accepts a filter
**          array structure for applications requiring event filtering.  In the current implementation
**          of the EVS, only the binary filtering scheme is supported.  See section TBD of the cFE
**          Application Programmer's Guide for a description of the behavior of binary filters.
**          Applications may call #CFE_EVS_Register more than once, but each call will wipe out all
**          filters registered by previous calls (filter registration is NOT cumulative).
**
** \par Assumptions, External Events, and Notes:
**          Note: Event filters can be added, deleted or modified by ground commands.  All filtering
**                schemes include a default setting that results in no filtering (such as #CFE_EVS_NO_FILTER
**                for binary filters).
**
**          <b> Filter Scheme: </b> Binary <BR>
**          <b> Code: </b> CFE_EVS_EventFilter_BINARY <BR>
**          <b> Filter Structure: </b>
**          \code
**                     typedef struct CFE_EVS_BinFilter {
**                           uint16  EventID,
**                           uint16  Mask ;
**                     } CFE_EVS_BinFilter_t;
**          \endcode
**
** \param[in] Filters            Pointer to an array of event message filters, or NULL if no filtering is desired.
**                               The structure of an event message filter depends on the FilterScheme selected.
**                               (see Filter Schemes mentioned above)
**
** \param[in] NumEventFilters    The number of event message filters included in this call.  This must be less than
**                               or equal to the maximum number of events allowed per application
**                               (#CFE_PLATFORM_EVS_MAX_EVENT_FILTERS).
**
** \param[in] FilterScheme       The event filtering scheme that this application will use.  For the first
**                               implementation of the event services, only filter type #CFE_EVS_EventFilter_BINARY
**                               will be supported.
**
** \return Execution status below or from #CFE_ES_GetAppID, see \ref CFEReturnCodes
** \retval #CFE_SUCCESS                 \copybrief CFE_SUCCESS
** \retval #CFE_EVS_APP_FILTER_OVERLOAD \copybrief CFE_EVS_APP_FILTER_OVERLOAD
** \retval #CFE_EVS_UNKNOWN_FILTER      \copybrief CFE_EVS_UNKNOWN_FILTER
** \retval #CFE_EVS_APP_ILLEGAL_APP_ID  \copybrief CFE_EVS_APP_ILLEGAL_APP_ID
** \retval #CFE_ES_BAD_ARGUMENT         \copybrief CFE_ES_BAD_ARGUMENT
**/
CFE_Status_t CFE_EVS_Register(const void *Filters, uint16 NumEventFilters, uint16 FilterScheme);

#endif // CFE_EVS_H