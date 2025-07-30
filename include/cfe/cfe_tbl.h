#ifndef CFE_TBL_H
#define CFE_TBL_H

#include <stdint.h>

#define CFE_TBL_FILEDEF(ObjName, TblName, Desc, Filename) \
CFE_TBL_FileDef_t CFE_TBL_FileDef = {#ObjName "\0", #TblName "\0", #Desc "\0", #Filename "\0", sizeof(ObjName)};

/**
 * @brief Mock initialization function - call before using TBL mock functionality
 */
void mock_tbl_init(void);

/**
 * @brief Perform standard table maintenance on the specified table
 *
 * This function will perform the standard table maintenance on the table
 * associated with the specified Table Handle.  This includes checking for
 * load/dump requests, updates, etc.  This function should be called on a
 * periodic basis.
 *
 * @param[in] TblHandle Handle of Table to be managed.
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS                   @copybrief CFE_SUCCESS
 * @retval #CFE_TBL_ERR_INVALID_HANDLE    @copybrief CFE_TBL_ERR_INVALID_HANDLE
 * @retval #CFE_TBL_INFO_UPDATED          @copybrief CFE_TBL_INFO_UPDATED
 * @retval #CFE_TBL_INFO_TABLE_LOADED     @copybrief CFE_TBL_INFO_TABLE_LOADED
 * @retval #CFE_TBL_INFO_DUMP_PENDING     @copybrief CFE_TBL_INFO_DUMP_PENDING
 * @retval #CFE_TBL_INFO_VALIDATION_PENDING @copybrief CFE_TBL_INFO_VALIDATION_PENDING
 * @retval #CFE_TBL_INFO_UPDATE_PENDING   @copybrief CFE_TBL_INFO_UPDATE_PENDING
 */
CFE_Status_t CFE_TBL_Manage(CFE_TBL_Handle_t TblHandle);

/**
 * @brief Obtain the current address of the contents of the specified table
 *
 * This function will return the current address of the specified table.
 * This function should be called immediately prior to using the contents
 * of the table.
 *
 * @param[out] TblPtr  Pointer to pointer to start of Table.  This will be
 *                     modified to point to the start of the Table.
 * @param[in]  TblHandle Handle of Table whose address is needed.
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS                   @copybrief CFE_SUCCESS
 * @retval #CFE_TBL_ERR_INVALID_HANDLE    @copybrief CFE_TBL_ERR_INVALID_HANDLE
 * @retval #CFE_TBL_ERR_UNREGISTERED      @copybrief CFE_TBL_ERR_UNREGISTERED
 * @retval #CFE_TBL_INFO_UPDATED          @copybrief CFE_TBL_INFO_UPDATED
 */
CFE_Status_t CFE_TBL_GetAddress(void **TblPtr, CFE_TBL_Handle_t TblHandle);

/**
 * @brief Release the pointer to the specified table
 *
 * This function will decrement the use counter for the specified table.
 * A table cannot be modified unless this use counter is zero.  This
 * function should be called when an application is finished using a table.
 *
 * @param[in] TblHandle Handle of Table to be released.
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS                   @copybrief CFE_SUCCESS
 * @retval #CFE_TBL_ERR_INVALID_HANDLE    @copybrief CFE_TBL_ERR_INVALID_HANDLE
 * @retval #CFE_TBL_ERR_NEVER_LOADED      @copybrief CFE_TBL_ERR_NEVER_LOADED
 */
CFE_Status_t CFE_TBL_ReleaseAddress(CFE_TBL_Handle_t TblHandle);

/**
 * @brief Register a table with cFE to obtain table management services
 *
 * This function will register the calling Application as the owner of a table.
 * This is done to allow the application to load, dump, and modify the
 * contents of the table.
 *
 * @param[out] TblHandlePtr  Pointer to int32 that will hold the handle of the table.  This handle is
 *                           required for other API calls when accessing the table.  This would be
 *                           the output of the function.
 * @param[in]  Name          Pointer to character string containing the desired name of the table.
 *                           This cannot be longer than #CFE_MISSION_TBL_MAX_NAME_LENGTH characters.
 * @param[in]  Size          Size, in bytes, of the table to be created.
 * @param[in]  TblOptionFlags Flag options that can be used to specify table characteristics.
 * @param[in]  TblValidationFuncPtr Pointer to function that should be called by Table Services
 *                                  to validate the contents of the table OR NULL if no validation
 *                                  function is desired.
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS                   @copybrief CFE_SUCCESS
 * @retval #CFE_TBL_ERR_INVALID_SIZE      @copybrief CFE_TBL_ERR_INVALID_SIZE
 * @retval #CFE_TBL_ERR_INVALID_NAME      @copybrief CFE_TBL_ERR_INVALID_NAME
 * @retval #CFE_TBL_ERR_BAD_APP_ID        @copybrief CFE_TBL_ERR_BAD_APP_ID
 * @retval #CFE_TBL_ERR_DUPLICATE_DIFF_SIZE @copybrief CFE_TBL_ERR_DUPLICATE_DIFF_SIZE
 * @retval #CFE_TBL_ERR_REGISTRY_FULL     @copybrief CFE_TBL_ERR_REGISTRY_FULL
 * @retval #CFE_TBL_WARN_DUPLICATE        @copybrief CFE_TBL_WARN_DUPLICATE
 */
CFE_Status_t CFE_TBL_Register(CFE_TBL_Handle_t *TblHandlePtr, const char *Name, size_t Size, uint16 TblOptionFlags, CFE_TBL_CallbackFuncPtr_t TblValidationFuncPtr);

/**
 * @brief Load a specified table with data from specified source
 *
 * This function will load the table associated with the specified table handle
 * with data from the specified source.
 *
 * @param[in] TblHandle Handle of Table to be loaded.
 * @param[in] SrcType   Flag indicating the nature of the given \c SrcDataPtr below.
 * @param[in] SrcDataPtr Pointer to data to be loaded into the table OR a character string
 *                       identifying the filename of the data to be loaded into the table.
 *
 * @return Execution status, see @ref CFEReturnCodes
 * @retval #CFE_SUCCESS                   @copybrief CFE_SUCCESS
 * @retval #CFE_TBL_ERR_INVALID_HANDLE    @copybrief CFE_TBL_ERR_INVALID_HANDLE
 * @retval #CFE_TBL_ERR_INVALID_SRC_TYPE  @copybrief CFE_TBL_ERR_INVALID_SRC_TYPE
 * @retval #CFE_TBL_ERR_LOAD_IN_PROGRESS  @copybrief CFE_TBL_ERR_LOAD_IN_PROGRESS
 * @retval #CFE_TBL_ERR_FILE_NOT_FOUND    @copybrief CFE_TBL_ERR_FILE_NOT_FOUND
 * @retval #CFE_TBL_ERR_FILE_SIZE_INCORRECT @copybrief CFE_TBL_ERR_FILE_SIZE_INCORRECT
 * @retval #CFE_TBL_ERR_NO_BUFFER_AVAIL   @copybrief CFE_TBL_ERR_NO_BUFFER_AVAIL
 */
CFE_Status_t CFE_TBL_Load(CFE_TBL_Handle_t TblHandle, CFE_TBL_SrcEnum_t SrcType, const void *SrcDataPtr);

#endif /* CFE_TBL_H */