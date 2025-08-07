# CFS CF Mock Project

Concept of this project is to leave CFS' CF (CFDP) app code untouched and yet have it run as a stand-alone.
The issue is that CF (aka CFDP) was originally designed to be built as part of the larger CFS (Core Flight System) 
project. To standalonify it we provide OSAL (the OS Abstraction Layer) and mock out symbols for the other CFE 
modules (EVS, ES, SB, TBL, TIME) it needs to help it feel at home ex-situ.

To keep the original CF and OSAL source code pristine, they are checked out as their original submodules. The
only thing unique about this project is the mock-outs and all the cmake glue.

## License

This project is licensed under the MIT License. See the LICENSE file for details.
