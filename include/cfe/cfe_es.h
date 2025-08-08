// filepath: /cfs-cf-mock/cfs-cf-mock/include/cfe/cfe_es.h
#ifndef CFE_ES_H
#define CFE_ES_H

// Mock function declarations for CFE Executive Services (ES)

#define CFE_ES_PerfLogExit(id) (CFE_ES_PerfLogAdd(id, 1))
#define CFE_ES_PerfLogEntry(id) (CFE_ES_PerfLogAdd(id, 0))

#include "common_types.h"
#include "cfe/cfe_idk.h"

/**
 * @brief Executive Services Application ID type 
 */
typedef CFE_RESOURCEID_BASE_TYPE CFE_ES_AppId_t;

/**
 * @brief Application run status values
 */
enum CFE_ES_RunStatus
{
    CFE_ES_RunStatus_APP_RUN = 1,             // Continue running
    CFE_ES_RunStatus_APP_ERROR = 3,           // Exit with error

    // Values below this line aren't used in mock, here for posterity
    CFE_ES_RunStatus_UNDEFINED = 0,           // Reserved value
    CFE_ES_RunStatus_APP_EXIT = 2,            // Normal exit
    CFE_ES_RunStatus_SYS_EXCEPTION = 4,       // App caused exception
    CFE_ES_RunStatus_SYS_RESTART = 5,         // System requests restart
    CFE_ES_RunStatus_SYS_RELOAD = 6,          // System requests reload
    CFE_ES_RunStatus_SYS_DELETE = 7,          // System requests stop
    CFE_ES_RunStatus_CORE_APP_INIT_ERROR = 8, // Core app init failed
    CFE_ES_RunStatus_CORE_APP_RUNTIME_ERROR = 9, // Core app runtime failure
    CFE_ES_RunStatus_MAX = 10                    // Maximum state marker
};

/**
 * @brief Mock initialization function - call before using ES mock functionality
 */
void mock_es_init(void);

/**
 * @brief Add a performance marker to the log
 * @param[in] Marker     Performance marker ID
 * @param[in] EntryExit  0=Entry, 1=Exit
 */
void CFE_ES_PerfLogAdd(uint32 Marker, uint32 EntryExit);

/**
 * @brief Write a printf-style string to the system log
 * @param[in] SpecStringPtr  Format string (printf-style)
 * @param[in] ...            Optional parameters for format string
 * @return CFE_SUCCESS on success, CFE_ES_ERR_SYS_LOG_FULL if log is full
 */
CFE_Status_t CFE_ES_WriteToSysLog(const char *SpecStringPtr, ...) OS_PRINTF(1, 2);

/**
 * @brief Check for exit requests and control application run loop
 * @param[in] RunStatus  Pointer to current loop status variable
 * @return false when application should terminate, true otherwise
 */
bool CFE_ES_RunLoop(uint32 *RunStatus);

/**
 * @brief Exit the calling application
 * @param[in] ExitStatus  Application exit status code
 */
void CFE_ES_ExitApp(uint32 ExitStatus);

/**
 * @brief Get the application ID for the calling application
 * @param[out] AppIdPtr  Pointer to receive the application ID
 * @return CFE_SUCCESS on success, CFE_ES_ERR_BUFFER on error
 */
CFE_Status_t CFE_ES_GetAppID(CFE_ES_AppId_t *AppIdPtr);

/**
 * @brief Get application name for the specified application ID
 * @param[out] AppName      Buffer to receive the application name
 * @param[in]  AppId        Application ID to query
 * @param[in]  BufferLength Length of the AppName buffer
 * @return CFE_SUCCESS on success, error code on failure
 */
CFE_Status_t CFE_ES_GetAppName(char *AppName, CFE_ES_AppId_t AppId, size_t BufferLength);

/**
 * @brief Register a child task associated with the calling application
 *
 * This function creates and registers a child task with the calling 
 * application. The child task is tracked for resource management and 
 * cleaned up when the parent application exits.
 *
 * @param[out] TaskIdPtr    Pointer to variable to receive the task ID
 * @param[in]  TaskName     Null terminated task name
 * @param[in]  FunctionPtr  Pointer to the task entry point function
 * @param[in]  StackPtr     Pointer to task stack (NULL for dynamic allocation)
 * @param[in]  StackSize    Size of the task stack in bytes
 * @param[in]  Priority     Task priority (lower numbers = higher priority)
 * @param[in]  Flags        Reserved for future use, should be 0
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS                  @copybrief CFE_SUCCESS
 * @retval #CFE_ES_ERR_CHILD_TASK_CREATE @copybrief CFE_ES_ERR_CHILD_TASK_CREATE
 * @retval #CFE_ES_ERR_CHILD_TASK_REGISTER @copybrief CFE_ES_ERR_CHILD_TASK_REGISTER
 */
CFE_Status_t CFE_ES_CreateChildTask(CFE_ES_TaskId_t *TaskIdPtr, 
    const char *TaskName, 
    CFE_ES_ChildTaskMainFuncPtr_t FunctionPtr, 
    CFE_ES_StackPointer_t StackPtr, 
    size_t StackSize, 
    CFE_ES_TaskPriority_t Priority, uint32 Flags);

/**
 * @brief Restart the cFE Core and all applications (does not return)
 * @param[in] RestartType  Type of restart to perform
 */
void CFE_ES_ResetCFE(uint32 RestartType);

#endif // CFE_ES_H