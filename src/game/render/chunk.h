#pragma once

#include <cglm/types-struct.h>
#include "shader.h"
#include "texture.h"
#include "../util/list.h"

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 8
#define BUFFER_SIZE CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT * 24

struct MeshInfo {
	u32 faceCount;
	u32 vertexCount;
	u32 uvCount;
	u32 indexCount;
	u32 uniqueIndexCount;
};

typedef struct Chunk {
	vec3s position;
	vec3s vertices[BUFFER_SIZE];
	vec2s uvs[BUFFER_SIZE];
	u32 indices[BUFFER_SIZE];
	struct MeshInfo info;
	u32 vao;
	u32 vertexVbo;
	u32 uvVbo;
	u32 ebo;
	Texture texture;
} Chunk;

Chunk createChunk(vec3s position);
void renderChunk(Chunk* chunk);
