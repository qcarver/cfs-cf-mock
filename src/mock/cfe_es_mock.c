#include <stdio.h>
#include "mock/cfe_es_mock.h"

// Mock implementation of CFE Executive Services (ES) functions

void CFE_ES_ApplicationInit(void)
{
    // Mock behavior for application initialization
    printf("Mock: CFE_ES_ApplicationInit called\n");
}

void CFE_ES_RunLoop(void)
{
    // Mock behavior for running the application loop
    printf("Mock: CFE_ES_RunLoop called\n");
}

void CFE_ES_RegisterApp(void)
{
    // Mock behavior for registering an application
    printf("Mock: CFE_ES_RegisterApp called\n");
}

void CFE_ES_GetAppID(void)
{
    // Mock behavior for getting the application ID
    printf("Mock: CFE_ES_GetAppID called\n");
}

// Add more mock functions as needed for other CFE ES functionalities