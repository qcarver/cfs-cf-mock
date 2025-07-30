# File: /cfs-cf-mock/cfs-cf-mock/cmake/InterceptorConfig.cmake

set(CFE_EVS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include/cfe")
set(CFE_ES_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include/cfe")
set(CFE_SB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include/cfe")
set(CFE_TBL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include/cfe")
set(CFE_TIME_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include/cfe")

set(CFE_EVS_MOCK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include/mock")
set(CFE_ES_MOCK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include/mock")
set(CFE_SB_MOCK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include/mock")
set(CFE_TBL_MOCK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include/mock")
set(CFE_TIME_MOCK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include/mock")

include_directories(${CFE_EVS_INCLUDE_DIR} ${CFE_ES_INCLUDE_DIR} ${CFE_SB_INCLUDE_DIR} ${CFE_TBL_INCLUDE_DIR} ${CFE_TIME_INCLUDE_DIR})
include_directories(${CFE_EVS_MOCK_INCLUDE_DIR} ${CFE_ES_MOCK_INCLUDE_DIR} ${CFE_SB_MOCK_INCLUDE_DIR} ${CFE_TBL_MOCK_INCLUDE_DIR} ${CFE_TIME_MOCK_INCLUDE_DIR})

# Redirect the build process to use mock implementations
set(CFE_EVS_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../src/mock/mock_evs.cs")
set(CFE_ES_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../src/mock/mock_es.cs")
set(CFE_SB_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../src/mock/mock_sb.cs")
set(CFE_TBL_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../src/mock/mock_tbl.cs")
set(CFE_TIME_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../src/mock/mock_time.cs")

# Add the mock libraries to the target
target_sources(cf PRIVATE ${CFE_EVS_LIBRARIES} ${CFE_ES_LIBRARIES} ${CFE_SB_LIBRARIES} ${CFE_TBL_LIBRARIES} ${CFE_TIME_LIBRARIES})