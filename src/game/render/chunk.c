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
#define FNL_IMPL
#include "../../include/FastNoiseLite.h"

static void appendFaceData(Chunk* chunk, FaceData data) {

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



static struct Heightmap generateChunk() {
	// Create and configure noise state
	fnl_state noise = fnlCreateState();
	noise.noise_type = FNL_NOISE_OPENSIMPLEX2;

	// Gather noise data
	struct Heightmap heightmap = {
		.heightVariation = 8,
		.minHeight = 4
	};

	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++) 
		{
			heightmap.data[x][y] = heightmap.minHeight + (heightmap.heightVariation * fnlGetNoise2D(&noise, x, y));
		}
	}

	return heightmap;
}

static void generateBlocks(Chunk* chunk) {

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int y = 0; y < CHUNK_HEIGHT; y++) {
				f32 columnHeight = chunk->heightmap.data[x][z];
				if (y < columnHeight && y >= columnHeight-1) {
					chunk->blocks[x][y][z] = createBlock((vec3s){{x, y, z}}, BLOCK_TYPE_GRASS);
				} else if (y < columnHeight-1 && y >= columnHeight-3) {
					chunk->blocks[x][y][z] = createBlock((vec3s){{x, y, z}}, BLOCK_TYPE_DIRT);
				} else if (y < columnHeight-3) {
					chunk->blocks[x][y][z] = createBlock((vec3s){{x, y, z}}, BLOCK_TYPE_STONE);
				} else {
					chunk->blocks[x][y][z] = createBlock((vec3s){{x, y, z}}, BLOCK_TYPE_EMPTY);
				}
			}
		}
	}
}

static void generateFaces(Chunk* chunk) {
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int y = 0; y < chunk->heightmap.data[x][z]; y++) {
				// Left faces: add if block to the left is empty or is farthest left in chunk
				if (x > 0) {
					if (chunk->blocks[x-1][y][z].type == BLOCK_TYPE_EMPTY) {
						appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_LEFT]);
					}
				} else {
					appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_LEFT]);
				}
				// Right faces: add if block to the right is empty or if is farthest right in chunk
				if (x < CHUNK_SIZE-1) {
					if (chunk->blocks[x][y][z].type == BLOCK_TYPE_EMPTY) {
						appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_RIGHT]);
					}
				} else {
					appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_RIGHT]);
				}
				// Front faces: add if block in front is empty or if is farthest forward in chunk
				if (z < CHUNK_SIZE-1) {
					if (chunk->blocks[x][y][z].type == BLOCK_TYPE_EMPTY) {
						appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_FRONT]);
					}
				} else {
					appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_FRONT]);
				}
				// Back faces: add if block behind is empty or if is farthest back in chunk
				if (z > 0) {
					if (chunk->blocks[x][y][z-1].type == BLOCK_TYPE_EMPTY) {
						appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_BACK]);
					}
				} else {
					appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_BACK]);
				}
				// Top faces: add if block above is empty or if is top in chunk
				if (y < chunk->heightmap.data[x][z]-1) {
					if (chunk->blocks[x][y][z].type == BLOCK_TYPE_EMPTY) {
						appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_TOP]);
					}
				} else {
					appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_TOP]);
				}
				// Bottom faces: add if block below is empty or if is lowest in chunk
				if (y > 0) {
					if (chunk->blocks[x][y-1][z].type == BLOCK_TYPE_EMPTY) {
						appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_BOTTOM]);
					}
				} else {
					appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_BOTTOM]);
				}
			}
		}
	}
	appendIndices(chunk);
}

static void buildChunk(Chunk* chunk) {

	vaoCreate(&chunk->vao);

	vboCreate(&chunk->vertexVbo, &chunk->vertices, sizeof(chunk->vertices), false);
	vaoAttrib(0, 3, 0, 0);

	vboCreate(&chunk->uvVbo, &chunk->uvs, sizeof(chunk->uvs), false);
	vaoAttrib(1, 2, 0, 0);

	eboCreate(&chunk->ebo, &chunk->indices, sizeof(chunk->indices), false);

	chunk->texture = textureCreate("assets/atlas.png");
	vboUnbind();
	vaoUnbind();
}

Chunk createChunk(vec3s position) {
	Chunk self = {
		.position = position,
		.heightmap = generateChunk(),
		.info = {0}
	};

	generateBlocks(&self);
	generateFaces(&self);
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

