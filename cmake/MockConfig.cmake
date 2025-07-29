set(MOCK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)

include_directories(${MOCK_INCLUDE_DIR})

# Mock CFE Event Services
add_library(cfe_evs_mock STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/mock/cfe_evs_mock.c
)

# Mock CFE Executive Services
add_library(cfe_es_mock STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/mock/cfe_es_mock.c
)

# Mock CFE Software Bus
add_library(cfe_sb_mock STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/mock/cfe_sb_mock.c
)

# Mock CFE Table Services
add_library(cfe_tbl_mock STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/mock/cfe_tbl_mock.c
)

# Mock CFE Time Services
add_library(cfe_time_mock STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/mock/cfe_time_mock.c
)

# Link mock libraries to the interceptor
target_link_libraries(build_interceptor
    cfe_evs_mock
    cfe_es_mock
    cfe_sb_mock
    cfe_tbl_mock
    cfe_time_mock
)