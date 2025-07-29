// filepath: /cfs-cf-mock/cfs-cf-mock/include/cfe/cfe_es.h
#ifndef CFE_ES_H
#define CFE_ES_H

// Mock function declarations for CFE Executive Services (ES)

#define CFE_ES_PerfLogExit(id) (CFE_ES_PerfLogAdd(id, 1))
#define CFE_ES_PerfLogEntry(id) (CFE_ES_PerfLogAdd(id, 0))

/**
 * @brief Add a mark to the performance log
 *
 * This function adds a mark to the performance log. The performance log is
 * a circular buffer that stores performance markers with timestamps.
 *
 * @param[in] Marker     Performance marker ID
 * @param[in] EntryExit  0=Entry, 1=Exit
 */
void CFE_ES_PerfLogAdd(uint32 Marker, uint32 EntryExit);

/**
 * @brief Write a string to the system log
 *
 * This function writes a printf style string to the system log.
 * The system log is a circular buffer that stores system messages.
 *
 * @param[in] SpecStringPtr  Pointer to a null terminated format string
 * @param[in] ...            Optional parameters for format string
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS      @copybrief CFE_SUCCESS
 */
CFE_Status_t CFE_ES_WriteToSysLog(const char *SpecStringPtr, ...) OS_PRINTF(1, 2);

/**
 * @brief Check for exit requests and return the current loop status
 *
 * This function provides the mechanism by which an app can be made aware
 * of pending shutdown requests. It is the application's responsibility to
 * call this function periodically and shutdown when appropriate. This
 * function also provides a means to control the run loop independently
 * of shutdown commands received from the ground.
 *
 * @param[in] RunStatus  Pointer to a variable containing the current loop status
 *                       This value controls when the loop terminates.
 *
 * @return false when the calling Application should terminate, true otherwise
 */
bool CFE_ES_RunLoop(uint32 *RunStatus);

/**
 * @brief Exit an application
 *
 * This function is called when an application needs to exit. This could be
 * called from the application main function when it detects an error that
 * makes it impossible to continue, or it could be called in response to a
 * command from the ground to exit the application.
 *
 * @param[in] ExitStatus  The application exit status
 */
void CFE_ES_ExitApp(uint32 ExitStatus);

/**
 * @brief Get the application ID for the calling application
 *
 * This function returns the application ID for the calling application.
 * The application ID is used to identify the application in other API calls.
 *
 * @param[out] AppIdPtr  Pointer to variable to be set to the calling application's ID
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS            @copybrief CFE_SUCCESS
 * @retval #CFE_ES_ERR_BUFFER      @copybrief CFE_ES_ERR_BUFFER
 */
CFE_Status_t CFE_ES_GetAppID(CFE_ES_AppId_t *AppIdPtr);

/**
 * @brief Get the application name for the specified application ID
 *
 * This function returns the application name for the specified application ID.
 *
 * @param[out] AppName      Pointer to buffer to receive the application name
 * @param[in]  AppId        Application ID to query
 * @param[in]  BufferLength Length of the AppName buffer
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS               @copybrief CFE_SUCCESS
 * @retval #CFE_ES_ERR_BUFFER         @copybrief CFE_ES_ERR_BUFFER
 * @retval #CFE_ES_ERR_RESOURCEID_NOT_VALID @copybrief CFE_ES_ERR_RESOURCEID_NOT_VALID
 */
CFE_Status_t CFE_ES_GetAppName(char *AppName, CFE_ES_AppId_t AppId, size_t BufferLength);

/**
 * @brief Register a child task associated with the calling application
 *
 * This function is called by an application to register a child task.
 * The child task is associated with the calling application for resource
 * tracking and cleanup purposes.
 *
 * @param[out] TaskIdPtr    Pointer to variable to receive the task ID
 * @param[in]  TaskName     Null terminated task name
 * @param[in]  FunctionPtr  Pointer to the task entry point function
 * @param[in]  StackPtr     Pointer to the task stack (may be NULL for dynamic allocation)
 * @param[in]  StackSize    Size of the task stack in bytes
 * @param[in]  Priority     Task priority (lower numbers are higher priority)
 * @param[in]  Flags        Reserved for future use, should be 0
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS                  @copybrief CFE_SUCCESS
 * @retval #CFE_ES_ERR_CHILD_TASK_CREATE @copybrief CFE_ES_ERR_CHILD_TASK_CREATE
 * @retval #CFE_ES_ERR_CHILD_TASK_REGISTER @copybrief CFE_ES_ERR_CHILD_TASK_REGISTER
 */
CFE_Status_t CFE_ES_CreateChildTask(CFE_ES_TaskId_t *TaskIdPtr, const char *TaskName, CFE_ES_ChildTaskMainFuncPtr_t FunctionPtr, CFE_ES_StackPointer_t StackPtr, size_t StackSize, CFE_ES_TaskPriority_t Priority, uint32 Flags);

/**
 * @brief Restart the cFE Core and all applications
 *
 * This function is used to restart the cFE Core and all of its applications.
 * This function does not return to the caller.
 *
 * @param[in] RestartType  Type of restart to perform
 */
void CFE_ES_ResetCFE(uint32 RestartType);

#endif // CFE_ES_H