#include <stdio.h>
#include "cf_cmd.h"
#include "mock/cfe_evs_mock.h"
#include "mock/cfe_es_mock.h"
#include "mock/cfe_sb_mock.h"
#include "mock/cfe_tbl_mock.h"
#include "mock/cfe_time_mock.h"

void setup_mock_interceptor() {
    // Initialize mock implementations
    mock_evs_init();
    mock_es_init();
    mock_sb_init();
    mock_tbl_init();
    mock_time_init();
}

int main(int argc, char *argv[]) {
    setup_mock_interceptor();

    printf("Starting CF Mock Test\n");
    
    // Create a mock wakeup command message
    CF_WakeupCmd_t wakeup_msg = {0};
    
    // Call the CF wakeup command
    CFE_Status_t status = CF_WakeupCmd(&wakeup_msg);
    
    printf("CF_WakeupCmd returned status: %d\n", (int)status);
    
    return 0;
}