#include "chunk.h"
#include "block.h"
#include "block_data.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "texture.h"
#include <glad/glad.h>
#include <cglm/struct.h>

static void appendVertices(Chunk* chunk, FaceData data) {

	for (int i = 0; i < 4; i++) {
		chunk->vertices[chunk->info.vertexCount]  = data.vertices[i];
		chunk->uvs[chunk->info.vertexCount] = data.uvs[i];
		chunk->info.vertexCount++;
	}
	chunk->info.faceCount++;
}

static void appendIndices(Chunk* chunk) {
	for (int i = 0; i < chunk->info.faceCount; i++) {
		chunk->indices[chunk->info.indexCount++] = 0 + chunk->info.uniqueIndexCount;
		chunk->indices[chunk->info.indexCount++] = 1 + chunk->info.uniqueIndexCount;
		chunk->indices[chunk->info.indexCount++] = 3 + chunk->info.uniqueIndexCount;
		chunk->indices[chunk->info.indexCount++] = 1 + chunk->info.uniqueIndexCount;
		chunk->indices[chunk->info.indexCount++] = 2 + chunk->info.uniqueIndexCount;
		chunk->indices[chunk->info.indexCount++] = 3 + chunk->info.uniqueIndexCount;
		chunk->info.uniqueIndexCount += 4;
	}
}

static void generateBlocks(Chunk* chunk) {
	for (int i = 0; i < 3; i++) {
		Block block = createBlock((vec3s){{i, 0.0f, 0.0f}});
		
		if (i == 0) {
			appendVertices(chunk, block.faces[BLOCK_FACE_LEFT]);
		}
		if (i == 2) {
			appendVertices(chunk, block.faces[BLOCK_FACE_RIGHT]);
		}
		appendVertices(chunk, block.faces[BLOCK_FACE_FRONT]);
		appendVertices(chunk, block.faces[BLOCK_FACE_BACK]);
		appendVertices(chunk, block.faces[BLOCK_FACE_TOP]);
		appendVertices(chunk, block.faces[BLOCK_FACE_BOTTOM]);

		appendIndices(chunk);
	}
}


static void buildChunk(Chunk* chunk) {

	vaoCreate(&chunk->vao);

	vboCreate(&chunk->vertexVbo, &chunk->vertices, sizeof(chunk->vertices), false);
	vaoAttrib(0, 3, 0, 0);

	vboCreate(&chunk->uvVbo, &chunk->uvs, sizeof(chunk->uvs), false);
	vaoAttrib(1, 2, 0, 0);

	eboCreate(&chunk->ebo, &chunk->indices, sizeof(chunk->indices), false);

	chunk->texture = textureCreate("assets/grass.png");
	vboUnbind();
	vaoUnbind();
}

Chunk createChunk(vec3s position) {
	Chunk self = {
		.position = position,
		.info = {0}
	};
	generateBlocks(&self);
	buildChunk(&self);

	return self;
}

void renderChunk(Chunk* chunk) {
	shaderBind(&shaders.shaderDefault);
	shaderUniform(&shaders.shaderDefault, "model", glms_translate(glms_mat4_identity(), chunk->position).raw[0]);
	vaoBind(chunk->vao);
	textureBind(chunk->texture.id);
	glDrawElements(GL_TRIANGLES, chunk->info.indexCount, GL_UNSIGNED_INT, 0);
}

