#include <stdio.h>
#include "cf_cmd.h"
#include "cfe/cfe_evs.h"
#include "cfe/cfe_es.h"
#include "cfe/cfe_sb.h"
#include "cfe/cfe_tbl.h"
#include "cfe/cfe_time.h"
#include <signal.h>
#include <stdint.h>

volatile uint32_t AppRunStatus = 0;

void setup_mock_interceptor() {
    // Initialize mock implementations
    mock_evs_init();
    mock_es_init();
    mock_sb_init();
    mock_tbl_init();
    mock_time_init();
}

void handle_sigint(int sig) {
    AppRunStatus = 0;
}

int main(int argc, char *argv[]) {
    setup_mock_interceptor();

    printf("Starting CF Mock Test\n");
    
    AppRunStatus = 1;

    // Register signal handler for Ctrl-C
    signal(SIGINT, handle_sigint);

    printf("Starting CF Mock Test\n");

    while (AppRunStatus) {
            // Create a mock wakeup command message
            CF_WakeupCmd_t wakeup_msg = {0};

            // Call the CF wakeup command
            CFE_Status_t status = CF_WakeupCmd(&wakeup_msg);

            printf("CF_WakeupCmd returned status: %d\n", (int)status);

            // Sleep or delay to avoid busy loop
            sleep(1);
        }

        printf("Exiting CF Mock Test\n");

    }
    
    return 0;
}