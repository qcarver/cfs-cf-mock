#ifndef CFE_ERROR_H
#define CFE_ERROR_H

#include <stdint.h>

/**
 * \brief cFE Status type for readability and eventually type safety
 */
typedef int32_t CFE_Status_t;

/**
 * @brief Successful execution
 *
 *  Operation was performed successfully
 */
#define CFE_SUCCESS ((CFE_Status_t)0)

/**
 * @brief System Log Full
 *
 *  The cFE system Log is full.
 *  This error means the message was not logged at all
 *
 */
#define CFE_ES_ERR_SYS_LOG_FULL ((CFE_Status_t)0xc4000006)

#endif