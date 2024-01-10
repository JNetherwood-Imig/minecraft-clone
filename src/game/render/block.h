#pragma once

#include "../util/types.h"
#include "../util/dictionary.h"
#include "block_data.h"
#include <cglm/types-struct.h>

typedef struct block {
	vec3s postiton;
	FaceData faces[6];
} Block;

Block createBlock(vec3s position);
FaceData getFace(Dictionary* dict, i32 face);
