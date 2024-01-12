#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../io.h"
#include "../util/utils.h"
#include "../util/types.h"

// Define file reading chunk size and basic error returns
#define IO_READ_CHUNK_SIZE 2097152
#define IO_READ_ERROR_GENERAL "Error reading file: %s. errno: %d\n"
#define IO_READ_ERROR_MEMORY "Not enough free memory to read file: %s\n"

// Function to safely read data from a file and store it in a File struct
File ioFileRead(const char* path) {
	// Initializes an empty file and sets it to invalid
	File file = { .isValid = false };

	// Opens file in read bytes mode and checks for errors
	FILE* fp = fopen(path, "rb");
	if (!fp || ferror(fp))
		ERROR_RETURN(file, IO_READ_ERROR_GENERAL, path, errno);

	// Initializes variables to store pointers and sizes
	char* data = NULL;
	char* tmp;
	usize used = 0;
	usize size = 0;
	usize n;

	// Loops through file in incraments of IO_READ_CHUNK_SIZE
	// until it reaches the end or is forced to exit because of an error
	while (true) {
		// Check if the bytes used + 1 IO_READ_CHUNK_SIZE incrament + 1
		//is greater than the size to be allocated,
		// expand the size to be allocated to fit
		if (used + IO_READ_CHUNK_SIZE + 1 > size) {
			size = used + IO_READ_CHUNK_SIZE + 1;

			// If enough memory was unable to be allocated, print an error and return
			if (size <= used) {
				free(data);
				ERROR_RETURN(file, "Input file is too large: %s\n", path);
			}

			// If memory was successfully allocated,
			// reallocate memory for the tmp string
			tmp = realloc(data, size);
			// If memory could not be allocated, print a memory error and return
			if (!tmp) {
				free(data);
				ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
			}
			data = tmp;
		}

		// Read bytes until the end of the file
		n = fread(data + used, 1, IO_READ_CHUNK_SIZE, fp);
		if (n == 0)
			break;

		// Incrament used bytes by n
		used += n;
	}

	// Check for file errors
	if (ferror(fp)) {
		free(data);
		ERROR_RETURN(file, IO_READ_ERROR_GENERAL, path, errno);
	}

	// Reallocate memory for the tmp data and check for errors
	tmp = realloc(data, used + 1);
	if (!tmp) {
		free(data);
		ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
	}
	data = tmp;
	data[used] = 0;

	// Set file data to data,
	// length to used bytes,
	// and the validity flag to true
	file.data = data;
	file.length = used;
	file.isValid = true;

	return file;
}

// Function to write a file to a given path
u8 ioFileWrite(void* buffer, usize size, const char* path) {
	// Open a file in write bytes mode and check for errors
	FILE* fp = fopen(path, "wb");
	if (!fp || ferror(fp))
		ERROR_RETURN(1, "Cannot write file: %s\n", path);

	// Write data to the file in 1 chunk
	usize chunksWritten = fwrite(buffer, size, 1, fp);
	
	fclose(fp);

	// If data could not be written in 1 chunk, return an error message
	if (chunksWritten != 1)
		ERROR_RETURN(1, "Write error. Expected 1 chunk, got %zu.\n", chunksWritten);

	// Return 0 for success
	return 0;
}
