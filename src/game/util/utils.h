#pragma once

#include <stdlib.h>
#include <stdio.h>

// Basic error macros for exiting and returning
#define ERROR_EXIT(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define ERROR_RETURN(R, ...) { fprintf(stderr, __VA_ARGS__); return R; }
