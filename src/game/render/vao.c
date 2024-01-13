#include "../../include/glad/glad.h"
#include "../util/types.h"

// Create a vao with the given id and make it active
void vaoCreate(u32* vao) {
	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);
}

// Make the given vao active
void vaoBind(u32* vao) {
	glBindVertexArray(*vao);
}

// Unbind active vao
void vaoUnbind(void) {
	glBindVertexArray(0);
}

// Create and enable a vertex attrib array
void vaoAttrib(u32 index, i32 size, u32 stride, u32 offset) {
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(f32), (void*)(offset * sizeof(f32)));
	glEnableVertexAttribArray(index);
}

// Delete vao
void vaoDelete(u32* vao) {
	glDeleteVertexArrays(1, vao);
}
