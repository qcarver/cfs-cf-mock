// filepath: /cfs-cf-mock/cfs-cf-mock/include/cfe/cfe_es.h
#ifndef CFE_ES_H
#define CFE_ES_H

// Mock function declarations for CFE Executive Services (ES)

// Function to initialize the Executive Services
void CFE_ES_InitApp(void);

// Function to register an application with the Executive Services
int32 CFE_ES_RegisterApp(void);

// Function to exit an application
void CFE_ES_ExitApp(void);

// Function to get the application ID
CFE_ES_AppId_t CFE_ES_GetAppID(void);

// Function to get the application name
const char* CFE_ES_GetAppName(CFE_ES_AppId_t AppId);

#endif // CFE_ES_H