#pragma once

#include "block_data.h"
#include <cglm/types-struct.h>

// Block struct to sore all attributes of a block
typedef struct Block {
	vec3s postiton;
	BlockType type;
	BlockTypeInfo* blockTypeInfo;
	FaceTypeInfo faceTypeInfo;
	FaceData faces[6];
} Block;

// Functiion prototype to return a block object given a position and type
Block createBlock(vec3s position, BlockType type);
