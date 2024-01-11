#pragma once

#include "block_data.h"
#include <cglm/types-struct.h>

typedef struct Block {
	vec3s postiton;
	FaceData faces[6];
} Block;

Block createBlock(vec3s position);
