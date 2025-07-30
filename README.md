# CFS CF Mock Project

Concept of this project is to leave CFS' CF (CFDP) cfe_app code untouched and yet have it run as a stand-alone
To do this we must mock out symbols for the other CFE modules (EVS, ES, SB, TBL, TIME) and intercept the
configuration of at-least CF's main root CMakeLists.txt file.

## Project Structure

The project is organized as follows:

```
cfs-cf-mock
├── src/
│   ├── main.c                   # Main executable with CF_WakeupCmd test
│   ├── mock_evs.c               # Mock implementations for CFE Event Services
│   ├── mock_es.c                # Mock implementations for CFE Executive Services
│   ├── mock_sb.c                # Mock implementations for CFE Software Bus
│   ├── mock_tbl.c               # Mock implementations for CFE Table Services
│   └── mock_time.c              # Mock implementations for CFE Time Services
├── include/
│   └── cfe/
│       ├── cfe_evs.h            # CFE EVS header with mock init function
│       ├── cfe_es.h             # CFE ES header with mock init function
│       ├── cfe_sb.h             # CFE SB header with mock init function
│       ├── cfe_tbl.h            # CFE TBL header with mock init function
│       └── cfe_time.h           # CFE TIME header with mock init function
├── CF/                          # Git submodule containing CF source code
├── CMakeLists.txt               # Main CMake configuration file
└── README.md                    # Project documentation
```

## License

This project is licensed under the MIT License. See the LICENSE file for details.