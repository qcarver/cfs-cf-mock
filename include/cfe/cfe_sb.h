// filepath: /cfs-cf-mock/cfs-cf-mock/include/cfe/cfe_sb.h
#ifndef CFE_SB_H
#define CFE_SB_H

#include "common_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Mock function declarations for CFE Software Bus (SB) services

/**
 * @brief Mock initialization function - call before using SB mock functionality
 */
void mock_sb_init(void);

/**
 * @brief Transmit a message
 *
 * This routine sends the specified message to all subscribers.  The software
 * bus will read the message ID from the message header to determine which
 * pipes should receive the message.
 *
 * @param[in] MsgPtr       A pointer to the message to be sent
 * @param[in] IsOrigination true if message is being originated by the caller,
 *                         false if the message is being relayed/forwarded
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS            @copybrief CFE_SUCCESS
 * @retval #CFE_SB_BAD_ARGUMENT    @copybrief CFE_SB_BAD_ARGUMENT
 * @retval #CFE_SB_MSG_TOO_BIG     @copybrief CFE_SB_MSG_TOO_BIG
 * @retval #CFE_SB_BUF_ALOC_ERR    @copybrief CFE_SB_BUF_ALOC_ERR
 */
CFE_Status_t CFE_SB_TransmitMsg(const CFE_MSG_Message_t *MsgPtr, bool IsOrigination);

/**
 * @brief Subscribe to a message on the software bus with default parameters
 *
 * This routine adds the specified pipe to the destination list for
 * the specified message ID.
 *
 * @param[in] MsgId   The message ID to subscribe to
 * @param[in] PipeId  The pipe ID to add to the destination list
 * @param[in] MsgLim  The maximum number of messages with this Message ID to
 *                    allow in this pipe at the same time.
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS                @copybrief CFE_SUCCESS
 * @retval #CFE_SB_BAD_ARGUMENT        @copybrief CFE_SB_BAD_ARGUMENT
 * @retval #CFE_SB_MAX_DESTS_MET       @copybrief CFE_SB_MAX_DESTS_MET
 * @retval #CFE_SB_BUF_ALOC_ERR        @copybrief CFE_SB_BUF_ALOC_ERR
 * @retval #CFE_SB_PIPE_FULL           @copybrief CFE_SB_PIPE_FULL
 */
CFE_Status_t CFE_SB_SubscribeLocal(CFE_SB_MsgId_t MsgId, CFE_SB_PipeId_t PipeId, uint16 MsgLim);

/**
 * @brief Subscribe to a message on the software bus
 *
 * This routine adds the specified pipe to the destination list for
 * the specified message ID.
 *
 * @param[in] MsgId   The message ID to subscribe to
 * @param[in] PipeId  The pipe ID to add to the destination list
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS                @copybrief CFE_SUCCESS
 * @retval #CFE_SB_BAD_ARGUMENT        @copybrief CFE_SB_BAD_ARGUMENT
 * @retval #CFE_SB_MAX_DESTS_MET       @copybrief CFE_SB_MAX_DESTS_MET
 * @retval #CFE_SB_BUF_ALOC_ERR        @copybrief CFE_SB_BUF_ALOC_ERR
 * @retval #CFE_SB_PIPE_FULL           @copybrief CFE_SB_PIPE_FULL
 */
CFE_Status_t CFE_SB_Subscribe(CFE_SB_MsgId_t MsgId, CFE_SB_PipeId_t PipeId);

/**
 * @brief Release an allocated message buffer
 *
 * This routine decrements the usecount of a message buffer, and returns
 * it to the pool if it becomes zero.
 *
 * @param[in] BufPtr  Pointer to the message buffer to release
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS          @copybrief CFE_SUCCESS
 * @retval #CFE_SB_BAD_ARGUMENT  @copybrief CFE_SB_BAD_ARGUMENT
 */
CFE_Status_t CFE_SB_ReleaseMessageBuffer(CFE_SB_Buffer_t *BufPtr);

/**
 * @brief Delete a pipe and clean up all data structures associated with it
 *
 * This routine deletes a pipe and cleans up the data structures associated
 * with it. The memory taken by the pipe is deallocated and returned to the
 * system.
 *
 * @param[in] PipeId  The pipe ID of the pipe to be deleted.
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS          @copybrief CFE_SUCCESS
 * @retval #CFE_SB_BAD_ARGUMENT  @copybrief CFE_SB_BAD_ARGUMENT
 */
CFE_Status_t CFE_SB_DeletePipe(CFE_SB_PipeId_t PipeId);

/**
 * @brief Convert a generic message ID value to a software bus message ID
 *
 * This routine converts a generic message ID value into a software bus
 * message ID that is type safe for SB APIs.
 *
 * @param[in] MsgIdValue  The generic message ID value
 *
 * @return The software bus message ID
 */
static inline CFE_SB_MsgId_t CFE_SB_ValueToMsgId(CFE_SB_MsgId_Atom_t MsgIdValue);

/**
 * @brief Convert a software bus message ID to a generic message ID value
 *
 * This routine converts a software bus message ID into a generic message ID
 * value that can be used in switch statements, printf calls, etc.
 *
 * @param[in] MsgId  The software bus message ID
 *
 * @return The generic message ID value
 */
static inline CFE_SB_MsgId_Atom_t CFE_SB_MsgIdToValue(CFE_SB_MsgId_t MsgId);

/**
 * @brief Transmit a message buffer
 *
 * This routine sends a previously allocated buffer to all subscribers.
 * This routine is normally used for sending messages that were received
 * and need to be forwarded or relayed to other applications.
 *
 * @param[in] BufPtr       Pointer to the buffer to be sent
 * @param[in] IsOrigination true if message is being originated by the caller,
 *                         false if the message is being relayed/forwarded
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS            @copybrief CFE_SUCCESS
 * @retval #CFE_SB_BAD_ARGUMENT    @copybrief CFE_SB_BAD_ARGUMENT
 * @retval #CFE_SB_BUFFER_INVALID  @copybrief CFE_SB_BUFFER_INVALID
 */
CFE_Status_t CFE_SB_TransmitBuffer(CFE_SB_Buffer_t *BufPtr, bool IsOrigination);

/**
 * @brief Sets the time field in a software bus message with the current spacecraft time
 *
 * This routine sets the time of a software bus message with the current
 * spacecraft time. This will be the time from the mission elapsed time (MET)
 * source that is identified by the Spacecraft Time task.
 *
 * @param[in] MsgPtr  Pointer to the message
 */
void CFE_SB_TimeStampMsg(CFE_MSG_Message_t *MsgPtr);

/**
 * @brief Receive a message from a software bus pipe
 *
 * This routine retrieves the next message from the specified pipe. If no
 * message is present at the pipe, this routine will block until either a
 * message arrives or the timeout value is reached.
 *
 * @param[out] BufPtr   Pointer to a pointer to the message buffer received.
 *                      The caller should cast this to the appropriate message type.
 * @param[in]  PipeId   The pipe ID of the pipe containing the message to be obtained.
 * @param[in]  TimeOut  The number of milliseconds to wait for a message to arrive on
 *                      the pipe before returning. If this parameter is set to
 *                      CFE_SB_PEND_FOREVER, the routine will wait indefinitely for a message to arrive.
 *                      If this parameter is set to CFE_SB_POLL, the routine will not wait for
 *                      a message to arrive.
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS          @copybrief CFE_SUCCESS
 * @retval #CFE_SB_BAD_ARGUMENT  @copybrief CFE_SB_BAD_ARGUMENT
 * @retval #CFE_SB_TIME_OUT      @copybrief CFE_SB_TIME_OUT
 * @retval #CFE_SB_PIPE_RD_ERR   @copybrief CFE_SB_PIPE_RD_ERR
 * @retval #CFE_SB_NO_MESSAGE    @copybrief CFE_SB_NO_MESSAGE
 */
CFE_Status_t CFE_SB_ReceiveBuffer(CFE_SB_Buffer_t **BufPtr, CFE_SB_PipeId_t PipeId, int32 TimeOut);

/**
 * @brief Create a new software bus pipe
 *
 * This routine creates a new software bus pipe. The pipe is a FIFO queue
 * that can hold a limited number of messages.
 *
 * @param[out] PipeIdPtr  Pointer to the variable that will store the pipe ID
 * @param[in]  Depth      The maximum number of messages that can be queued on this pipe
 * @param[in]  PipeName   A string to be used to identify this pipe
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS          @copybrief CFE_SUCCESS
 * @retval #CFE_SB_BAD_ARGUMENT  @copybrief CFE_SB_BAD_ARGUMENT
 * @retval #CFE_SB_PIPE_CR_ERR   @copybrief CFE_SB_PIPE_CR_ERR
 * @retval #CFE_SB_MAX_PIPES_MET @copybrief CFE_SB_MAX_PIPES_MET
 */
CFE_Status_t CFE_SB_CreatePipe(CFE_SB_PipeId_t *PipeIdPtr, uint16 Depth, const char *PipeName);

/**
 * @brief Allocate a message buffer for sending a software bus message
 *
 * This routine allocates a buffer from the software bus buffer pool.
 * The buffer is initialized and ready to be populated with message data.
 *
 * @param[in] MsgSize  The size of the message buffer to allocate
 *
 * @return Pointer to the allocated message buffer, or NULL on error
 */
CFE_SB_Buffer_t* CFE_SB_AllocateMessageBuffer(size_t MsgSize);

#ifdef __cplusplus
}
#endif

#endif // CFE_SB_H