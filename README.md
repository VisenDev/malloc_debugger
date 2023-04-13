# malloc_debugger
A very simple library for finding memory leaks

# how to use
Simply download debug.c and debug.h and include the debug.h in any files you want to debug. Then, call `audit_memory()` on program exit to check for leaks

Make sure to update `#include "debug.h"` in debug.c to use the proper path for your project

Additionally, the current configuration only supports up to 1024 calls to malloc, but this can easily be expanded if necessary by changing the size `memory_records` in debug.c 
