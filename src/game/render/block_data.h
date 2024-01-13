#pragma once

#include "../../include/cglm/types-struct.h"
#include "../util/types.h"

// Store block faces for easy access
typedef enum BlockFace {
	BLOCK_FACE_FRONT,
	BLOCK_FACE_BACK,
	BLOCK_FACE_LEFT,
	BLOCK_FACE_RIGHT,
	BLOCK_FACE_TOP,
	BLOCK_FACE_BOTTOM
} BlockFace;

// Store block types in a way that is clear to read,
// as well as the enum length for the creation of the arrays
typedef enum BlockType {
	BLOCK_TYPE_EMPTY,
	BLOCK_TYPE_GRASS,
	BLOCK_TYPE_DIRT,
	BLOCK_TYPE_STONE,
	BLOCK_TYPE_ENUM_LENGTH
} BlockType;

// Store all face types and an enum length for arrays
typedef enum FaceType {
	FACE_TYPE_GRASS_TOP,
	FACE_TYPE_GRASS_SIDE,
	FACE_TYPE_DIRT,
	FACE_TYPE_STONE,
	FACE_TYPE_ENUM_LENGTH
} FaceType;

// Face data struct to store a coordinate and uv for each vertex in a face
typedef struct FaceData {
    vec3s vertices[4];
    vec2s uvs[4];
} FaceData;

// Struct for storing atlas positions for the appropriate texture
// for each face type
typedef struct FaceTypeInfo {
	u32 column;
	u32 row;
} FaceTypeInfo;

// Stores a face type for each face in a block
typedef struct BlockTypeInfo {
	FaceType faceType[6];
} BlockTypeInfo;

// Create external arrays to store
// default block vertex coordinates,
// info for each face type,
// and face type info for each block type
extern vec3s vertexData[6][4];
extern FaceTypeInfo* faceTypeInfo[FACE_TYPE_ENUM_LENGTH];
extern BlockTypeInfo* blockTypeInfo[BLOCK_TYPE_ENUM_LENGTH];
