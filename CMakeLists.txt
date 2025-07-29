project(CFS_CF_MOCK C)

# Specify the include directories
include_directories(include)

# Specify the source files for the mock implementations
set(MOCK_SRC_FILES
  src/mock/cfe_evs_mock.c
  src/mock/cfe_es_mock.c
  src/mock/cfe_sb_mock.c
  src/mock/cfe_tbl_mock.c
  src/mock/cfe_time_mock.c
  src/interceptor/build_interceptor.c
)

# Create the mock library
add_library(cfs_cf_mock STATIC ${MOCK_SRC_FILES})

# Specify the include directories for the mock library
target_include_directories(cfs_cf_mock PUBLIC include/mock include/cfe)

# Optionally, you can add any necessary configurations or dependencies here
# For example, linking with other libraries if needed

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