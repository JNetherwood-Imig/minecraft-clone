#include "chunk.h"
#include "block.h"
#include "block_data.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "texture.h"
#include <string.h>
#include <glad/glad.h>
#include <cglm/struct/mat4.h>
#include <cglm/struct.h>

void genChunk(Chunk* chunk);

static void addFaceVertices(Chunk* chunk, Block* block, BlockFace face, u32 faceCount) {
	memcpy(&chunk->vertices[face + faceCount], &block->faces[face], sizeof(block->faces));
}

static void addFaceIndices(Chunk* chunk, u32 amount) {
	u32 indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	for (int i = 0; i < amount; i++) {
		chunk->indices[i] = indices;

		chunk->indexCount += 4;
	}
}

void genBlocks(Chunk* chunk) {
	chunk->indexCount = 0;
	for (int i = 0; i < 3; i++) {
		Block block = createBlock((vec3s){{i, 0, 0}});

		u32 faceCount = 0;
		for (int j = 0; j < 6; j++) {
			addFaceVertices(chunk, &block, j, i * 6);
		}

		faceCount += 6;

		addFaceIndices(chunk, faceCount);
	}
}


void buildChunk(Chunk* chunk) {

	vaoCreate(&chunk->vao);

	vboCreate(&chunk->vertexVbo, &chunk->vertices, sizeof(chunk->vertices), false);
	vaoAttrib(0, 3, 0, 0);

	vboCreate(&chunk->uvVbo, &chunk->uvs, sizeof(chunk->uvs), false);
	vaoAttrib(1, 2, 0, 0);

	eboCreate(&chunk->ebo, &chunk->indices, sizeof(chunk->indices), false);

	chunk->texture = textureCreate("assets/grass.png");
	vaoUnbind();
	vboUnbind();
}

Chunk createChunk(vec3s position) {
	Chunk chunk = { .position = position };
	genBlocks(&chunk);
	buildChunk(&chunk);

	return chunk;
}

void renderChunk(Chunk* chunk, Shader* shader) {
	shaderBind(shader);
	shaderUniform(shader, "model", (f32*)glms_translate(glms_mat4_identity(), chunk->position).raw);
	vaoBind(chunk->vao);
	textureBind(chunk->texture.id);
	glDrawElements(GL_TRIANGLES, chunk->indexCount, GL_UNSIGNED_INT, 0);
}

