#ifndef CFE_ES_MOCK_H
#define CFE_ES_MOCK_H

#include <stdint.h>
#include <stdbool.h>

// Mock function declarations for CFE Executive Services (ES)

// Function to initialize the ES
void CFE_ES_InitApp(void);

// Function to register an application with ES
int32_t CFE_ES_RegisterApp(void);

// Function to exit an application
void CFE_ES_ExitApp(void);

// Function to get the application ID
uint32_t CFE_ES_GetAppID(void);

// Function to get the application name
const char* CFE_ES_GetAppName(uint32_t AppId);

// Function to check if an application is running
bool CFE_ES_IsAppRunning(uint32_t AppId);

// Add more mock function declarations as needed

#endif // CFE_ES_MOCK_H