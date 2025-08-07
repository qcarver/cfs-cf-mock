#ifndef CFE_ERROR_H
#define CFE_ERROR_H

#include "common_types.h" 

/**
 * @brief cFE Status type for readability and type safety
 */
typedef int32_t CFE_Status_t;

/**
 * @brief Successful execution
 */
#define CFE_SUCCESS ((CFE_Status_t)0)

/**
 * @brief System Log Full - message was not logged
 */
#define CFE_ES_ERR_SYS_LOG_FULL ((CFE_Status_t)0xc4000006)

#endif