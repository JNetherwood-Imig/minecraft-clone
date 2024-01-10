#pragma once

#include <cglm/types-struct.h>
#include "shader.h"
#include "texture.h"
#include "../util/list.h"

#define CHUNK_SIZE 16;
#define CHUNK_HEIGHT 8;

static const u32 CHUNK_VOLUME = 16 * 16 * 8;


typedef struct chunk {
	vec3s vertices[16 * 16 * 8 * 6][4];
	vec2s uvs[16 * 16 * 8 * 6][4];
	u32* indices[16 * 16 * 8 * 6 * 4];
	vec3s position;
	u32 indexCount;
	u32 vao;
	u32 vertexVbo;
	u32 uvVbo;
	u32 ebo;
	Texture texture;
} Chunk;

Chunk createChunk(vec3s position);
void renderChunk(Chunk* chunk, Shader* shader);
