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
 * @brief Transmit a message to all subscribers
 * @param[in] MsgPtr       Pointer to the message to be sent
 * @param[in] IsOrigination true if message is being originated, false if relayed
 * @return CFE_SUCCESS on success, error code on failure
 */
CFE_Status_t CFE_SB_TransmitMsg(const CFE_MSG_Message_t *MsgPtr, bool IsOrigination);

/**
 * @brief Subscribe to a message with message limit
 * @param[in] MsgId   The message ID to subscribe to
 * @param[in] PipeId  The pipe ID to add to the destination list
 * @param[in] MsgLim  Maximum number of messages allowed in pipe at once
 * @return CFE_SUCCESS on success, error code on failure
 */
CFE_Status_t CFE_SB_SubscribeLocal(CFE_SB_MsgId_t MsgId, CFE_SB_PipeId_t PipeId, uint16 MsgLim);

/**
 * @brief Subscribe to a message with default parameters
 * @param[in] MsgId   The message ID to subscribe to
 * @param[in] PipeId  The pipe ID to add to the destination list
 * @return CFE_SUCCESS on success, error code on failure
 */
CFE_Status_t CFE_SB_Subscribe(CFE_SB_MsgId_t MsgId, CFE_SB_PipeId_t PipeId);

/**
 * @brief Release an allocated message buffer
 * @param[in] BufPtr  Pointer to the message buffer to release
 * @return CFE_SUCCESS on success, error code on failure
 */
CFE_Status_t CFE_SB_ReleaseMessageBuffer(CFE_SB_Buffer_t *BufPtr);

/**
 * @brief Delete a pipe and clean up associated data structures
 * @param[in] PipeId  The pipe ID of the pipe to be deleted
 * @return CFE_SUCCESS on success, error code on failure
 */
CFE_Status_t CFE_SB_DeletePipe(CFE_SB_PipeId_t PipeId);

/**
 * @brief Convert a generic message ID value to software bus message ID
 * @param[in] MsgIdValue  The generic message ID value
 * @return The software bus message ID
 */
static inline CFE_SB_MsgId_t CFE_SB_ValueToMsgId(CFE_SB_MsgId_Atom_t MsgIdValue);

/**
 * @brief Convert software bus message ID to generic message ID value
 * @param[in] MsgId  The software bus message ID
 * @return The generic message ID value
 */
static inline CFE_SB_MsgId_Atom_t CFE_SB_MsgIdToValue(CFE_SB_MsgId_t MsgId);

/**
 * @brief Transmit a previously allocated buffer to all subscribers
 * @param[in] BufPtr       Pointer to the buffer to be sent
 * @param[in] IsOrigination true if message is being originated, false if relayed
 * @return CFE_SUCCESS on success, error code on failure
 */
CFE_Status_t CFE_SB_TransmitBuffer(CFE_SB_Buffer_t *BufPtr, bool IsOrigination);

/**
 * @brief Set message timestamp to current spacecraft time
 * @param[in] MsgPtr  Pointer to the message
 */
void CFE_SB_TimeStampMsg(CFE_MSG_Message_t *MsgPtr);

/**
 * @brief Receive a message from a software bus pipe
 * @param[out] BufPtr   Pointer to receive the message buffer
 * @param[in]  PipeId   The pipe ID to receive from
 * @param[in]  TimeOut  Timeout in milliseconds (CFE_SB_PEND_FOREVER or CFE_SB_POLL)
 * @return CFE_SUCCESS on success, error code on failure
 */
CFE_Status_t CFE_SB_ReceiveBuffer(CFE_SB_Buffer_t **BufPtr, CFE_SB_PipeId_t PipeId, int32 TimeOut);

/**
 * @brief Create a new software bus pipe (FIFO queue)
 * @param[out] PipeIdPtr  Pointer to receive the pipe ID
 * @param[in]  Depth      Maximum number of messages that can be queued
 * @param[in]  PipeName   String identifier for this pipe
 * @return CFE_SUCCESS on success, error code on failure
 */
CFE_Status_t CFE_SB_CreatePipe(CFE_SB_PipeId_t *PipeIdPtr, uint16 Depth, const char *PipeName);

/**
 * @brief Allocate a message buffer from the software bus buffer pool
 * @param[in] MsgSize  The size of the message buffer to allocate
 * @return Pointer to allocated buffer, or NULL on error
 */
CFE_SB_Buffer_t* CFE_SB_AllocateMessageBuffer(size_t MsgSize);

#ifdef __cplusplus
}
#endif

#endif // CFE_SB_H