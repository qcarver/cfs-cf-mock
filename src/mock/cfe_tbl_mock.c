#include "cfe_tbl_mock.h"

void CFE_TBL_Init(void) {
    // Mock implementation for CFE_TBL_Init
}

int32 CFE_TBL_Load(uint32 *TableHandle, const char *TableName, const char *Filename) {
    // Mock implementation for CFE_TBL_Load
    return CFE_SUCCESS;
}

int32 CFE_TBL_GetAddress(void **TblPtr, uint32 TableHandle) {
    // Mock implementation for CFE_TBL_GetAddress
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