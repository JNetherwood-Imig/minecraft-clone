#include <stdbool.h>
#include "../../include/glad/glad.h"
#include "../util/types.h"

// Abstraction for binding a vbo
void vboBind(u32* vbo) {
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
}

// Abstraction for unbinding active vbo
void vboUnbind(void) {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Function to create a vbo from an array of vertices
void vboCreate(u32* vbo, void* data, usize size, bool dynamic) {
	// Generate and bind vbo
	glGenBuffers(1, vbo);
	vboBind(vbo);
	// Set buffer data
	glBufferData(GL_ARRAY_BUFFER, size, data, dynamic? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

// Abstraction for deleting a vbo
void vboDelete(u32* vbo) {
	glDeleteBuffers(1, vbo);
}
