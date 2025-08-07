// filepath: /cfs-cf-mock/cfs-cf-mock/include/cfe/cfe_time.h
#ifndef CFE_TIME_H
#define CFE_TIME_H

#include "common_types.h"

/** 
 ** \brief Mock initialization function - call before using TIME mock functionality
 **/
void mock_time_init(void);

/**
**  \brief Data structure used to hold system time values
**
**  \par Description
**       The #CFE_TIME_SysTime_t data structure is used to hold time
**       values.  Time is referred to as the elapsed time (in seconds
**       and subseconds) since a specified epoch time.  The subseconds
**       field contains the number of 2^(-32) second intervals that have
**       elapsed since the epoch.
**
*/
typedef struct CFE_TIME_SysTime
{
    uint32 Seconds;    /**< \brief Number of seconds since epoch */
    uint32 Subseconds; /**< \brief Number of subseconds since epoch (LSB = 2^(-32) seconds) */
} CFE_TIME_SysTime_t;

/**
** \brief Get the current spacecraft time
**
** \par Description
**        This routine returns the current spacecraft time, which is the amount of
**        time elapsed since the epoch as set in mission configuration.  The time returned
**        is either TAI (no leap seconds) or UTC (including leap seconds).  This choice
**        is made in the mission configuration file by defining either #CFE_MISSION_TIME_CFG_DEFAULT_TAI
**        or #CFE_MISSION_TIME_CFG_DEFAULT_UTC as true at compile time.  To maintain re-usability
**        across missions, most applications should be using this function
**        rather than the specific routines for getting UTC/TAI directly.
**
** \return The current spacecraft time in default format
******************************************************************************/
CFE_TIME_SysTime_t CFE_TIME_GetTime(void);


#endif