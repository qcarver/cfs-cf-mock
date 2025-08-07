#ifndef CFE_TBL_H
#define CFE_TBL_H

#include "common_types.h"

#define CFE_TBL_FILEDEF(ObjName, TblName, Desc, Filename) \
CFE_TBL_FileDef_t CFE_TBL_FileDef = {#ObjName "\0", #TblName "\0", #Desc "\0", #Filename "\0", sizeof(ObjName)};

/**
 * @brief Mock initialization function - call before using TBL mock functionality
 */
void mock_tbl_init(void);

/**
 * @brief Perform standard table maintenance (load/dump requests, updates, etc.)
 * @param[in] TblHandle Handle of Table to be managed
 * @return CFE_SUCCESS on success, info codes for pending operations, error code on failure
 */
CFE_Status_t CFE_TBL_Manage(CFE_TBL_Handle_t TblHandle);

/**
 * @brief Get current address of the specified table contents
 * @param[out] TblPtr    Pointer to receive the table start address
 * @param[in]  TblHandle Handle of Table whose address is needed
 * @return CFE_SUCCESS on success, error code on failure
 */
CFE_Status_t CFE_TBL_GetAddress(void **TblPtr, CFE_TBL_Handle_t TblHandle);

/**
 * @brief Release the pointer to the specified table
 * @param[in] TblHandle Handle of Table to be released
 * @return CFE_SUCCESS on success, error code on failure
 */
CFE_Status_t CFE_TBL_ReleaseAddress(CFE_TBL_Handle_t TblHandle);

/**
 * @brief Register a table with cFE to obtain table management services
 *
 * Registers the calling application as the owner of a table to allow
 * loading, dumping, and modifying table contents.
 *
 * @param[out] TblHandlePtr        Pointer to receive the table handle
 * @param[in]  Name                Table name (max CFE_MISSION_TBL_MAX_NAME_LENGTH chars)
 * @param[in]  Size                Size in bytes of the table to be created
 * @param[in]  TblOptionFlags      Table characteristic flags
 * @param[in]  TblValidationFuncPtr Validation function pointer or NULL
 * @return CFE_SUCCESS on success, error code on failure
 */
CFE_Status_t CFE_TBL_Register(CFE_TBL_Handle_t *TblHandlePtr, const char *Name, size_t Size, 
                               uint16 TblOptionFlags, CFE_TBL_CallbackFuncPtr_t TblValidationFuncPtr);

/**
 * @brief Load a specified table with data from specified source
 * @param[in] TblHandle  Handle of Table to be loaded
 * @param[in] SrcType    Source type flag for SrcDataPtr interpretation
 * @param[in] SrcDataPtr Pointer to data or filename string to load
 * @return CFE_SUCCESS on success, error code on failure
 */
CFE_Status_t CFE_TBL_Load(CFE_TBL_Handle_t TblHandle, CFE_TBL_SrcEnum_t SrcType, const void *SrcDataPtr);

#endif /* CFE_TBL_H */