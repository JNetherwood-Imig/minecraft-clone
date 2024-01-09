#pragma once

#include <cglm/types-struct.h>
#include "shader.h"
#include "../util/list.h"

const u8 CHUNK_SIZE = 16;
const u16 CHUNK_HEIGHT = 8;

typedef struct chunk {
	List vertices;
	List uvs;
	List indices;
	vec3s position;
} Chunk;

Chunk createChunk(vec3s position);
void genChunk(Chunk* chunk);
void genBlocks(Chunk* chunk);
void buildChunk(Chunk* chunk);
void renderChunk(Chunk* chunk, Shader shader);
