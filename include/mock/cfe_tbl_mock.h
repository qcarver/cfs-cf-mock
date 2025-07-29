#ifndef CFE_TBL_MOCK_H
#define CFE_TBL_MOCK_H

#include <stdint.h>
#include <stdbool.h>

// Mock function declarations for CFE Table Services (TBL)

// Function to initialize the TBL mock
void CFE_TBL_Init(void);

// Function to load a table
int32_t CFE_TBL_Load(uint32_t *TableHandle, const char *TableName, const char *Filename);

// Function to get a table's address
void *CFE_TBL_GetAddress(uint32_t *TableHandle);

// Function to release a table's address
int32_t CFE_TBL_ReleaseAddress(uint32_t *TableHandle);

// Function to validate a table
bool CFE_TBL_Validate(uint32_t *TableHandle);

// Function to dump a table's contents
void CFE_TBL_Dump(uint32_t *TableHandle);

#endif // CFE_TBL_MOCK_H