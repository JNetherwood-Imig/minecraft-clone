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

BlockTypeInfo grassTopInfo = {
	.column = 0,
	.row = 0
};

BlockTypeInfo grassSideInfo = {
	.column = 1,
	.row = 0
};

BlockTypeInfo dirtInfo = {
	.column = 2,
	.row = 0
};

BlockTypeInfo* typeInfo[3] = {
	&grassTopInfo,
	&grassSideInfo,
	&dirtInfo
};
