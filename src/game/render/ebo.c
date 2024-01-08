#include <stdbool.h>
#include <glad/glad.h>
#include "../types.h"

// Function to bind an ebo
void eboBind(u32* ebo) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
}

// Function to unbind active ebo
void eboUnbind(void) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Function to create an ebo with an array of data
void eboCreate(u32* ebo, void* data, usize size, bool dynamic) {
	glGenBuffers(1, ebo);
	eboBind(ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, dynamic? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

// Abstraction for deleting a buffer
void eboDelete(u32* ebo) {
	glDeleteBuffers(1, ebo);
}
