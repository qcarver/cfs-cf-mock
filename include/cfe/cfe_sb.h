// filepath: /cfs-cf-mock/cfs-cf-mock/include/cfe/cfe_sb.h
#ifndef CFE_SB_H
#define CFE_SB_H

#include "common_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Abstract Message Base Types
 *
 * The concrete definition of these is provided by "cfe_msg_hdr.h" which is
 * user-selectable depending on the actual desired message definition. These
 * abstract types are used in the API definition; the API is defined based
 * on these abstract types, independent of the actual message definition.
 */

/**
 * @brief cFS generic base message
 */
typedef union CFE_MSG_Message CFE_MSG_Message_t;

/**
 * @brief Option used with #CFE_SB_ReceiveBuffer to request immediate pipe status
 */
#define CFE_SB_POLL 0  

/**
 * @brief Invalid Message ID for static/compile-time data initialization
 */
#define CFE_SB_INVALID_MSG_ID ((CFE_SB_MsgId_t)-1)

/**
 * @brief Time Out. Packet not received in the time given in the "timeout" parameter
 */
#define CFE_SB_TIME_OUT ((CFE_Status_t)0xca000001)

/**
 * @brief No Message. There was not a message on the pipe when polling
 */
#define CFE_SB_NO_MESSAGE ((CFE_Status_t)0xca000002)

// SB Types

/**
 * @brief CFE_SB_MsgId_Atom_t primitive type definition
 *
 * This is an integer type capable of holding any Message ID value
 * Note: This value is limited via #CFE_PLATFORM_SB_HIGHEST_VALID_MSGID
 */
typedef uint32 CFE_SB_MsgId_Atom_t;

/**
 * @brief CFE_SB_MsgId_t type definition
 *
 * Software Bus message identifier used in many SB APIs
 *
 * Currently this is directly mapped to the underlying holding type (not wrapped) for
 * compatibility with existing usage semantics in apps (mainly switch/case statements)
 *
 * @note In a future version it could become a type-safe wrapper similar to the route index,
 * to avoid message IDs getting mixed between other integer values.
 */
typedef CFE_SB_MsgId_Atom_t CFE_SB_MsgId_t;

/**
 * @brief CFE_SB_PipeId_t to primitive type definition
 *
 * Software Bus pipe identifier used in many SB APIs, as well as SB Telemetry messages
 * and data files.
 */
typedef uint32 CFE_SB_PipeId_t;

/**
 * @brief Reserved Message ID value for invalid/uninitialized message IDs
 */
#define CFE_SB_MSGID_RESERVED ((CFE_SB_MsgId_t)0)

/**
 * @brief Software Bus generic message buffer with alignment
 */
typedef union CFE_SB_Msg
{
    CFE_MSG_Message_t Msg;        /**< \brief Base message type without enforced alignment */
    long long int     LongInt;    /**< \brief Align to support Long Integer */
    long double       LongDouble; /**< \brief Align to support Long Double */
} CFE_SB_Buffer_t;

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