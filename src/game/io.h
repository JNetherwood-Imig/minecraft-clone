#pragma once

#include <stdbool.h>
#include "util/types.h"

// Define file struct with data, size, length, and validity flag
typedef struct File {
	char* data;
	usize length;
	bool isValid;
} File;

// Define function prototypes for reading and writing files
File ioFileRead(const char* path);
u8 ioFileWrite(void* buffer, usize size, const char* path);
