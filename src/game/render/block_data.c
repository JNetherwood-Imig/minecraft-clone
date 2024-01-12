#include "block_data.h"

// Define 2d array of vec3s' to store vertex data for a block
vec3s vertexData[6][4] = {

	// Front
	{
		{{ -0.5f,  0.5f,  0.5f }}, // Top left
		{{  0.5f,  0.5f,  0.5f }}, // Top right
		{{  0.5f, -0.5f,  0.5f }}, // Bottom right
		{{ -0.5f, -0.5f,  0.5f }}  // Bottom left
	},
	// Back
	{
		{{  0.5f,  0.5f, -0.5f }},
		{{ -0.5f,  0.5f, -0.5f }},
		{{ -0.5f, -0.5f, -0.5f }},
		{{  0.5f, -0.5f, -0.5f }}
	},
	// Left
	{
		{{ -0.5f,  0.5f, -0.5f }},
		{{ -0.5f,  0.5f,  0.5f }},
		{{ -0.5f, -0.5f,  0.5f }},
		{{-0.5f, -0.5f, -0.5f }}
	},
	// Right
	{
		{{  0.5f,  0.5f,  0.5f }},
		{{  0.5f,  0.5f, -0.5f }},
		{{  0.5f, -0.5f, -0.5f }},
		{{  0.5f, -0.5f,  0.5f }}
	},
	// Top
	{
		{{ -0.5f,  0.5f, -0.5f }},
		{{  0.5f,  0.5f, -0.5f }},
		{{  0.5f,  0.5f,  0.5f }},
		{{ -0.5f,  0.5f,  0.5f }}
	},
	// Bottom
	{
		{{ -0.5f, -0.5f,  0.5f }},
		{{  0.5f, -0.5f,  0.5f }},
		{{  0.5f, -0.5f, -0.5f }},
		{{ -0.5f, -0.5f, -0.5f }}
	}
};

// Face type info containing texture atlas positions
FaceTypeInfo grassTopInfo = {
	.column = 0,
	.row = 0
};

FaceTypeInfo grassSideInfo = {
	.column = 1,
	.row = 0
};

FaceTypeInfo dirtInfo = {
	.column = 2,
	.row = 0
};

FaceTypeInfo stoneInfo = {
	.column = 3,
	.row = 0
};

// External face type info array
FaceTypeInfo* faceTypeInfo[FACE_TYPE_ENUM_LENGTH] = {
	&grassTopInfo,
	&grassSideInfo,
	&dirtInfo,
	&stoneInfo
};

// Stores face types for each block type
BlockTypeInfo grassBlockInfo = {
	.faceType = {
		FACE_TYPE_GRASS_SIDE, // Front face
		FACE_TYPE_GRASS_SIDE, // Back face
		FACE_TYPE_GRASS_SIDE, // Left face
		FACE_TYPE_GRASS_SIDE, // Right face
		FACE_TYPE_GRASS_TOP,  // Top face
		FACE_TYPE_DIRT        // Bottom face
	}
};

BlockTypeInfo dirtBlockInfo = {
	.faceType = {
		FACE_TYPE_DIRT,
		FACE_TYPE_DIRT,
		FACE_TYPE_DIRT,
		FACE_TYPE_DIRT,
		FACE_TYPE_DIRT,
		FACE_TYPE_DIRT
	}
};

BlockTypeInfo stoneBlockInfo = {
	.faceType = {
		FACE_TYPE_STONE,
		FACE_TYPE_STONE,
		FACE_TYPE_STONE,
		FACE_TYPE_STONE,
		FACE_TYPE_STONE,
		FACE_TYPE_STONE
	}
};

// External block type info array
BlockTypeInfo* blockTypeInfo[BLOCK_TYPE_ENUM_LENGTH] = {
	NULL, // BLOCK_TYPE_EMPTY
	&grassBlockInfo,
	&dirtBlockInfo,
	&stoneBlockInfo
};