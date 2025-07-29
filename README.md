# CFS CF Mock Project

This project provides mock implementations for the CFS (Core Flight System) dependencies, specifically targeting the components with the naming conventions CFE_(EVS|ES|SB|TBL|TIME). The purpose of these mocks is to facilitate unit testing and development by intercepting the build process of the existing CFS_CF project.

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

## Usage

To use the mock implementations in your project, follow these steps:

1. **Include the Mock Project**: Add the mock project to your CMake configuration using `add_subdirectory()`.

2. **Link Against Mocks**: Ensure that your target links against the mock libraries instead of the actual CFS libraries.

3. **Build the Project**: Compile your project as usual. The build interceptor will redirect calls to the CFS dependencies to the mock implementations.

## Contribution

Contributions to enhance the mock implementations or improve the project structure are welcome. Please submit a pull request or open an issue for discussion.

## License

This project is licensed under the MIT License. See the LICENSE file for details.