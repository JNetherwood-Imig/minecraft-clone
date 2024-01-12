#include "block_data.h"

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

FaceTypeInfo* faceTypeInfo[FACE_TYPE_ENUM_LENGTH] = {
	&grassTopInfo,
	&grassSideInfo,
	&dirtInfo,
	&stoneInfo
};

BlockTypeInfo grassBlockInfo = {
	.faceType = {
		FACE_TYPE_GRASS_SIDE,
		FACE_TYPE_GRASS_SIDE,
		FACE_TYPE_GRASS_SIDE,
		FACE_TYPE_GRASS_SIDE,
		FACE_TYPE_GRASS_TOP,
		FACE_TYPE_DIRT
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

BlockTypeInfo* blockTypeInfo[BLOCK_TYPE_ENUM_LENGTH] = {
	NULL,
	&grassBlockInfo,
	&dirtBlockInfo,
	&stoneBlockInfo
};