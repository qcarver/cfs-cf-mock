cmake_minimum_required(VERSION 3.10)
project(CFS_CF_MOCK C)

# Set up overrides for CF submodule before including it
set(CFS_IO_LIB_MISSION_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CFE_EDS_ENABLED_BUILD FALSE)
set(ENABLE_UNIT_TESTS FALSE)

# Override add_cfe_app and add_cfe_tables to do nothing
function(add_cfe_app)
    # Do nothing - override CF's function
endfunction()

function(add_cfe_tables)
    # Do nothing - override CF's function  
endfunction()

# Add CF as a submodule
add_subdirectory(CF EXCLUDE_FROM_ALL)

# Specify the include directories - our mock CFE headers take precedence
include_directories(BEFORE include/cfe)
include_directories(include/mock)

# Specify the source files for the mock implementations
set(MOCK_SRC_FILES
  src/mock/cfe_evs_mock.c
  src/mock/cfe_es_mock.c
  src/mock/cfe_sb_mock.c
  src/mock/cfe_tbl_mock.c
  src/mock/cfe_time_mock.c
)

# Create the mock library
add_library(cfs_cf_mock STATIC ${MOCK_SRC_FILES})

# Specify the include directories for the mock library
target_include_directories(cfs_cf_mock PUBLIC 
  include/mock 
  include/cfe
  CF/fsw/inc  # Include CF headers
)

# Get CF source files (assuming they're in CF/fsw/src)
file(GLOB CF_SRC_FILES "CF/fsw/src/*.c")

# Create executable with main function
add_executable(cf_mock_test 
  src/main.c
  ${CF_SRC_FILES}
)

# Link the executable with our mock library
target_link_libraries(cf_mock_test cfs_cf_mock)

# Set include directories for the executable
target_include_directories(cf_mock_test PRIVATE
  include/cfe
  include/mock
  CF/fsw/inc
  CF/fsw/src # alas, CF also puts include files in here.
)

# Install the mock library and headers
install(TARGETS cfs_cf_mock
  EXPORT cfs_cf_mockTargets
  ARCHIVE DESTINATION lib
)

install(DIRECTORY include/mock/ DESTINATION include/mock)
install(DIRECTORY include/cfe/ DESTINATION include/cfe)

# Add configuration files for the mock project
include(CMakePackageConfigHelpers)
configure_package_config_file(cmake/MockConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/MockConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cfs_cf_mock"
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/MockConfig.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cfs_cf_mock"
)

# Add configuration files for the interceptor
configure_package_config_file(cmake/InterceptorConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/InterceptorConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cfs_cf_mock"
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/InterceptorConfig.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cfs_cf_mock"
)