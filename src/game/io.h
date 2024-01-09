#pragma once

#include <stdbool.h>
#include "util/types.h"

typedef struct file {
	char* data;
	usize len;
	bool isValid;
} File;

File ioFileRead(const char* path);
int ioFileWrite(void* buffer, usize size, const char* path);
