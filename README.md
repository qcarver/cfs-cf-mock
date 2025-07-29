# CFS CF Mock Project

Concept of this project is to leave CFS' CF (CFDP) cfe_app code untouched and yet have it run as a stand-alone
To do this we must mock out symbols for the other CFE modules (EVS, ES, SB, TBL, TIME) and intercept the
configuration of at-least CF's main root CMakeLists.txt file.

## Project Structure

The project is organized as follows:

```
cfs-cf-mock
├── src
│   ├── mock
│   │   ├── cfe_evs_mock.c       # Mock implementations for CFE Event Services
│   │   ├── cfe_es_mock.c        # Mock implementations for CFE Executive Services
│   │   ├── cfe_sb_mock.c        # Mock implementations for CFE Software Bus
│   │   ├── cfe_tbl_mock.c       # Mock implementations for CFE Table Services
│   │   └── cfe_time_mock.c      # Mock implementations for CFE Time Services
│   └── interceptor
│       └── build_interceptor.c   # Entry point for the build interceptor
├── include
│   ├── mock
│   │   ├── cfe_evs_mock.h       # Header for CFE EVS mock functions
│   │   ├── cfe_es_mock.h        # Header for CFE ES mock functions
│   │   ├── cfe_sb_mock.h        # Header for CFE SB mock functions
│   │   ├── cfe_tbl_mock.h       # Header for CFE TBL mock functions
│   │   └── cfe_time_mock.h      # Header for CFE TIME mock functions
│   └── cfe
│       ├── cfe_evs.h            # Placeholder for actual CFE EVS header
│       ├── cfe_es.h             # Placeholder for actual CFE ES header
│       ├── cfe_sb.h             # Placeholder for actual CFE SB header
│       ├── cfe_tbl.h            # Placeholder for actual CFE TBL header
│       └── cfe_time.h           # Placeholder for actual CFE TIME header
├── cmake
│   ├── MockConfig.cmake         # Configuration for the mock project
│   └── InterceptorConfig.cmake  # Configuration for the build interceptor
├── CMakeLists.txt               # Main CMake configuration file
└── README.md                    # Project documentation
```

## License

This project is licensed under the MIT License. See the LICENSE file for details.