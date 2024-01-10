#include "chunk.h"
#include "block.h"
#include "block_data.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "texture.h"
#include <glad/glad.h>
#include <cglm/struct/mat4.h>
#include <cglm/struct.h>

void genChunk(Chunk* chunk);
static void addFaceIndices(Chunk* chunk, u32 amount) {
	u32 indices[4] = {
		0 + chunk->indexCount,
		1 + chunk->indexCount,
		2 + chunk->indexCount,
		3 + chunk->indexCount
	};
	for (int i = 0; i < amount; i++) {
		addNode(&chunk->indices, &indices[0]);
		addNode(&chunk->indices, &indices[1]);
		addNode(&chunk->indices, &indices[3]);
		addNode(&chunk->indices, &indices[1]);
		addNode(&chunk->indices, &indices[2]);
		addNode(&chunk->indices, &indices[3]);

		chunk->indexCount += 4;
	}
}

void genBlocks(Chunk* chunk) {
	chunk->indexCount = 0;
	for (int i = 0; i < 3; i++) {
		Block block = createBlock((vec3s){i, 0, 0});

		u32 faceCount = 0;

		FaceData frontFaceData = block.faces[BLOCK_FACE_FRONT];
		addNode(&chunk->vertices, &frontFaceData.vertices);
		addNode(&chunk->uvs, &frontFaceData.uvs);

		FaceData backFaceData = block.faces[BLOCK_FACE_BACK];
		addNode(&chunk->vertices, &backFaceData.vertices);
		addNode(&chunk->uvs, &backFaceData.uvs);

		FaceData leftFaceData = block.faces[BLOCK_FACE_LEFT];
		addNode(&chunk->vertices, &leftFaceData.vertices);
		addNode(&chunk->uvs, &leftFaceData.uvs);

		FaceData rightFaceData = block.faces[BLOCK_FACE_RIGHT];
		addNode(&chunk->vertices, &rightFaceData.vertices);
		addNode(&chunk->uvs, &rightFaceData.uvs);

		FaceData topFaceData = block.faces[BLOCK_FACE_TOP];
		addNode(&chunk->vertices, &topFaceData.vertices);
		addNode(&chunk->uvs, &topFaceData.uvs);

		FaceData bottomFaceData = block.faces[BLOCK_FACE_BOTTOM];
		addNode(&chunk->vertices, &bottomFaceData.vertices);
		addNode(&chunk->uvs, &bottomFaceData.uvs);

		faceCount += 6;

		addFaceIndices(&chunk, faceCount);
	}
}


void buildChunk(Chunk* chunk) {

	vaoCreate(&chunk->vao);

	vboCreate(&chunk->vertexVbo, &chunk->vertices, sizeof(&chunk->vertices), false);
	vaoAttrib(0, 3, 0, 0);

	vboCreate(&chunk->uvVbo, &chunk->uvs, sizeof(&chunk->uvs), false);
	vaoAttrib(1, 2, 0, 0);

	eboCreate(&chunk->ebo, &chunk->indices, sizeof(&chunk->indices), false);

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
	glUniformMatrix4fv(glGetUniformLocation(&shader->id, "model"), 1, GL_FALSE, (const GLfloat*)glms_translate(glms_mat4_identity(), chunk->position).raw);
	vaoBind(&chunk->vao);
	textureBind(chunk->texture.id);
	glDrawElements(GL_TRIANGLES, chunk->indexCount, GL_UNSIGNED_INT, 0);
}

