#include <stdio.h>
#include "mock/cfe_evs_mock.h"
#include "mock/cfe_es_mock.h"
#include "mock/cfe_sb_mock.h"
#include "mock/cfe_tbl_mock.h"
#include "mock/cfe_time_mock.h"

void setup_mock_interceptor() {
    // Initialize mock implementations
    cfe_evs_mock_init();
    cfe_es_mock_init();
    cfe_sb_mock_init();
    cfe_tbl_mock_init();
    cfe_time_mock_init();
}

int main(int argc, char *argv[]) {
    setup_mock_interceptor();

    // Redirect build process to use mock implementations
    printf("Build interceptor initialized. Using mock implementations.\n");

    // Here you would typically call the build process or the application entry point
    // For example: return run_application(argc, argv);

    return 0;
}