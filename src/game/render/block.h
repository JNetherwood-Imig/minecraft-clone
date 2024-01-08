#pragma once

#include <cglm/types.h>
#include "../types.h"

typedef struct {
	u8 atlasRow;
	u8 atlasCollumn;
	f32 xOffsetClose;
	f32 xOffsetFar;
	f32 yOffsetClose;
	f32 yOffsetFar;
} BlockType;

typedef struct {
	u32 vao;
	u32 vbo;
	u32 ebo;
	mat4 model;
	BlockType type;
} Block;

Block createBlock(BlockType* type);

void renderBlock(Block* block, vec3 position);
