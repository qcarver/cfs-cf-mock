cmake_minimum_required(VERSION 3.10)
project(CFS_CF_MOCK C)

# Directory structure:
# cfdp-standalone/
# ├── CMakeLists.txt          <-- <<<YOU ARE HERE>>> 
# ├── cf/                     <-- your standalone CFDP logic
# │   └── CMakeLists.txt
# ├── osal/                   <-- OSAL (as a submodule)
# ├── build/                  <-- out-of-source build dir
# ├── install/
# │   └── osal/               <-- OSAL headers + libs go here
# └── cmake/                  <-- optional custom find modules

# <osal>
# Create directories if they don't exist
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/install ${CMAKE_CURRENT_BINARY_DIR}/osal)

# Do OSAL stuff first. CF will be looking for it
# OSAL has no dependencies, can build & install as an "ExternalProject" (CMAKE module emulating a user build.)
include(ExternalProject)
ExternalProject_Add(osal_project
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/osal
  BINARY_DIR ${CMAKE_BINARY_DIR}/osal
  CMAKE_ARGS
    -DOSAL_SYSTEM_BSPTYPE=generic-linux
    -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/install/osal
  INSTALL_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --target install
  BUILD_ALWAYS 1
  EXCLUDE_FROM_ALL TRUE
)

# Path to OSAL install
set(OSAL_INSTALL_DIR "${CMAKE_SOURCE_DIR}/install/osal")
set(OSAL_INCLUDE_DIR "${OSAL_INSTALL_DIR}/include")
set(OSAL_LIB_DIR     "${OSAL_INSTALL_DIR}/lib")

# Make sure OSAL is usable
if(NOT EXISTS "${OSAL_LIB_DIR}/libosal.a")
  message(FATAL_ERROR "OSAL static lib not found at ${OSAL_LIB_DIR}/libosal.a. \
Did you run OSAL's CMake build + install step?")
endif()

# Include + link OSAL
include_directories(${OSAL_INCLUDE_DIR})
link_directories(${OSAL_LIB_DIR})

# </osal>

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

# Specify the source files for the mock implementations
set(MOCK_SRC_FILES
  src/mock_evs.c
  src/mock_es.c
  src/mock_sb.c
  src/mock_tbl.c
  src/mock_time.c
)

# Create the mock library
add_library(cfs_cf_mock STATIC ${MOCK_SRC_FILES})

# Specify the include directories for the mock library
target_include_directories(cfs_cf_mock PUBLIC 
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
  CF/fsw/inc
  CF/fsw/src # alas, CF also puts include files in here.
)

# Install the mock library and headers
install(TARGETS cfs_cf_mock
  EXPORT cfs_cf_mockTargets
  ARCHIVE DESTINATION lib
)

install(DIRECTORY include/cfe/ DESTINATION include/cfe)