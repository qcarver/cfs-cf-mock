#include "cfe_sb_mock.h"

void CFE_SB_Init(void)
{
    // Mock initialization code for CFE SB
}

CFE_SB_PipeId_t CFE_SB_CreatePipe(const char *PipeName)
{
    // Mock implementation for creating a software bus pipe
    return 0; // Return a mock pipe ID
}

int32 CFE_SB_Subscribe(CFE_SB_MsgId_t MsgId, CFE_SB_PipeId_t PipeId)
{
    // Mock implementation for subscribing to a message
    return CFE_SUCCESS; // Return success
}

int32 CFE_SB_SendMsg(CFE_SB_Msg_t *MsgPtr)
{
    // Mock implementation for sending a message
    return CFE_SUCCESS; // Return success
}

int32 CFE_SB_RcvMsg(CFE_SB_Msg_t **MsgPtr, CFE_SB_PipeId_t PipeId, int32 Timeout)
{
    // Mock implementation for receiving a message
    return CFE_SUCCESS; // Return success
}

void CFE_SB_DeletePipe(CFE_SB_PipeId_t PipeId)
{
    // Mock implementation for deleting a software bus pipe
}