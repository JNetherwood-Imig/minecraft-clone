#pragma once

#include <cglm/types-struct.h>

typedef enum BlockFace {
	BLOCK_FACE_FRONT,
	BLOCK_FACE_BACK,
	BLOCK_FACE_LEFT,
	BLOCK_FACE_RIGHT,
	BLOCK_FACE_TOP,
	BLOCK_FACE_BOTTOM
} BlockFace;

typedef struct FaceData {
    vec3s vertices[4];
    vec2s* uvs;
} FaceData;

extern vec3s vertexData[6][4];
extern vec2s uvData[4];
