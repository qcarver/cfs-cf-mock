// filepath: /cfs-cf-mock/cfs-cf-mock/include/cfe/cfe_sb.h
#ifndef CFE_SB_H
#define CFE_SB_H

#ifdef __cplusplus
extern "C" {
#endif

// Mock function declarations for CFE Software Bus (SB) services

void CFE_SB_Init(void);
void CFE_SB_SendMsg(void *msg);
void CFE_SB_Subscribe(uint32_t msg_id, uint32_t pipe_id);
void CFE_SB_Unsubscribe(uint32_t msg_id, uint32_t pipe_id);
void CFE_SB_GetMsgId(void *msg);
void CFE_SB_GetMsgSize(void *msg);
void CFE_SB_Publish(void *msg);

#ifdef __cplusplus
}
#endif

#endif // CFE_SB_H