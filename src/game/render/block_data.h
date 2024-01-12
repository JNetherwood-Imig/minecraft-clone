#pragma once

#include <cglm/types-struct.h>
#include "../util/types.h"

typedef enum BlockFace {
	BLOCK_FACE_FRONT,
	BLOCK_FACE_BACK,
	BLOCK_FACE_LEFT,
	BLOCK_FACE_RIGHT,
	BLOCK_FACE_TOP,
	BLOCK_FACE_BOTTOM
} BlockFace;

typedef enum BlockType {
	BLOCK_TYPE_EMPTY,
	BLOCK_TYPE_GRASS,
	BLOCK_TYPE_DIRT
} BlockType;

typedef enum FaceType {
	FACE_TYPE_GRASS_TOP,
	FACE_TYPE_GRASS_SIDE,
	FACE_TYPE_DIRT
} FaceType;

typedef enum UvPositions {
	UV_TOP_LEFT,
	UV_TOP_RIGHT,
	UV_BOTTOM_RIGHT,
	UV_BOTTOM_LEFT
} UvPositions;

typedef struct FaceData {
    vec3s vertices[4];
    vec2s uvs[4];
} FaceData;

typedef struct BlockTypeInfo {
	u32 column;
	u32 row;
} BlockTypeInfo;

extern vec3s vertexData[6][4];
extern BlockTypeInfo* typeInfo[3];
