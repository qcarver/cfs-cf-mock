#ifndef CFE_SB_MOCK_H
#define CFE_SB_MOCK_H

#include <stdint.h>
#include <stdbool.h>

// Mock function declarations for CFE Software Bus (SB) functions

void CFE_SB_Init(void);
int32_t CFE_SB_SendMsg(void *MsgPtr);
int32_t CFE_SB_Subscribe(uint32_t MsgId, uint32_t PipeId);
int32_t CFE_SB_Unsubscribe(uint32_t MsgId, uint32_t PipeId);
int32_t CFE_SB_GetMsgId(void *MsgPtr);
bool CFE_SB_IsValidMsgId(uint32_t MsgId);

#endif /* CFE_SB_MOCK_H */