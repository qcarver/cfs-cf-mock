#include <stdio.h>
#include <stdint.h>
#include "cfe/cfe_tbl.h"

// Mock implementation of CFE Table Services (TBL) functions
CF_ConfigTable_t cf_mock_config = {
    .DownlinkChanEnabled = {1, 0},     // Enable CH0, disable CH1 (or tweak as needed)
    .RxPlaybackChan = 0,               // Use CH0 for RX playback
    .PlaybackChunkSize = 8,            // Segments of 8 bytes (low, but safe for testing)
    .AckTimeout = 5,                   // 5 seconds before retransmit ACK
    .NakTimeout = 5,                   // 5 seconds before NAK retry
    .InactivityTimeout = 30,           // 30 seconds before session timeout
    .OutgoingFileChunkSize = 512       // Chunk outgoing files into 128-byte segments
};

void CFE_TBL_Init(void) {
    // Mock implementation for CFE_TBL_Init
}

CFE_Status_t CFE_TBL_Manage(CFE_TBL_Handle_t TblHandle)
{
    // Mock skeleton implementation
    return CFE_SUCCESS;
}

// Returns a pointer to our statically allocated mock table. Nothing to see here.
CFE_Status_t CFE_TBL_GetAddress(void **TblPtr, CFE_TBL_Handle_t TblHandle)
{
    if (TblPtr)
        *TblPtr = &cf_mock_config;
    return CFE_SUCCESS;
}

CFE_Status_t CFE_TBL_ReleaseAddress(CFE_TBL_Handle_t TblHandle)
{
    // Mock skeleton implementation
    return CFE_SUCCESS;
}

// Register returns a dummy handle - we already statically allocated for our table-of-one.
CFE_Status_t CFE_TBL_Register(CFE_TBL_Handle_t *TblHandlePtr, const char *Name, size_t Size, uint16 TblOptionFlags, CFE_TBL_CallbackFuncPtr_t TblValidationFuncPtr)
{
    if (TblHandlePtr)
        *TblHandlePtr = 0;  // Only one table
    return CFE_SUCCESS;
}

CFE_Status_t CFE_TBL_Load(CFE_TBL_Handle_t TblHandle, CFE_TBL_SrcEnum_t SrcType, const void *SrcDataPtr)
{
    // Mock skeleton implementation
    return CFE_SUCCESS;
}

int32 CFE_TBL_Unload(uint32 TableHandle) {
    // Mock implementation for CFE_TBL_Unload
    return CFE_SUCCESS;
}

int32 CFE_TBL_Delete(uint32 TableHandle) {
    // Mock implementation for CFE_TBL_Delete
    return CFE_SUCCESS;
}

int32 CFE_TBL_GetStatus(uint32 TableHandle) {
    // Mock implementation for CFE_TBL_GetStatus
    return CFE_SUCCESS;
}