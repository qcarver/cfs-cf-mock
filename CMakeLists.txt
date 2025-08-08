cmake_minimum_required(VERSION 3.10)
project(CFS_CF_MOCK C)

# Okay, here's the gist of this CMake file. We are trying to build CF (aka CFDP)
# but it's usually build as part of the larger CFS (Core Flight System) project.
# To make it feel at home, we will mock out the parts of CFS that CF depends on.
# Additionally, CF depends on OSAL (the OS Abstraction Layer), for OS calls. So
# we have to build some version of CFS' OSAL as well.

# TL;DR: This CMake file sets up a standalone build for CFDP (CF) with mocked CFS and real OSAL dependencies. OSAL is standalone so it is build first, then CF is built with mocked CFS components.

# useful links:
# https://github.com/nasa/cf
# https://github.com/nasa/cfs
# https://github.com/nasa/osal

# Root Directory structure:
# cfdp-standalone/
# ├── CMakeLists.txt          <-- <<<YOU ARE HERE>>> 
# ├── cf/                     <-- CF (as a submodule) 
# ├── osal/                   <-- OSAL (as a submodule)
# ├── include/                <-- mocks for CF-used declarations typically in CFS
# ├── src/                    <-- mocks for CF-used definitions typically in CFS 
# ├── build/                  <-- created at CMake time if not already present 
# └── install/                <-- created at CMake time if not already present

# <osal>
# Create directories if they don't exist
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/install )

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
  BUILD_ALWAYS 0 # Change to 1 if you want to rebuild OSAL every time 
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

add_dependencies(cfs_cf_mock osal_project)

# Specify the include directories for the mock library
target_include_directories(cfs_cf_mock PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/include/cfe
  ${CMAKE_CURRENT_SOURCE_DIR}/CF/fsw/inc  # Include CF headers
  ${CMAKE_CURRENT_SOURCE_DIR}/CF/fsw/src  # unfortunately, there are ".h" files here too
)

# Get CF source files (assuming they're in CF/fsw/src)
file(GLOB CF_SRC_FILES "CF/fsw/src/*.c")

# Create executable with main function
add_executable(cf_mock_test 
  src/main.c
  ${CF_SRC_FILES}
)
# Ensure OSAL is built before cf_mock_test
add_dependencies(cf_mock_test osal_project)

# Link the executable with our mock library
target_link_libraries(cf_mock_test cfs_cf_mock osal)

# Set include directories for the executable
target_include_directories(cf_mock_test PRIVATE
  include/cfe
  CF/fsw/inc
  CF/fsw/src # alas, CF also puts include files in here.
)

install(DIRECTORY include/cfe/ DESTINATION include/cfe)