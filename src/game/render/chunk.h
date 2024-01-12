#pragma once

#include <cglm/types-struct.h>
#include "block.h"
#include "shader.h"
#include "texture.h"

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 32
#define BUFFER_SIZE CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT * 36

typedef struct Heightmap {
	u32 minHeight;
	u32 heightVariation;
	f32 data[CHUNK_SIZE][CHUNK_SIZE];
} Heightmap;

typedef struct MeshInfo {
	u32 faceCount;
	u32 vertexCount;
	u32 uvCount;
	u32 indexCount;
	u32 uniqueIndexCount;
} MeshInfo;

typedef struct Chunk {
	vec3s position;
	vec3s vertices[BUFFER_SIZE];
	vec2s uvs[BUFFER_SIZE];
	u32 indices[BUFFER_SIZE];
	Block blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
	u32 vao;
	u32 vertexVbo;
	u32 uvVbo;
	u32 ebo;
	Heightmap heightmap;
	MeshInfo info;
} Chunk;

Chunk createChunk(vec3s position);
void renderChunk(Chunk* chunk);
