#include "block_data.h"
#include <cglm/types-struct.h>

static vec3s rawVertexData[6][4] = {

	// Front
	{
		{ -0.5f,  0.5f,  0.5f },
		{  0.5f,  0.5f,  0.5f },
		{  0.5f, -0.5f,  0.5f },
		{ -0.5f, -0.5f,  0.5f }
	},
	// Back
	{
		{  0.5f,  0.5f, -0.5f },
		{ -0.5f,  0.5f, -0.5f },
		{ -0.5f, -0.5f, -0.5f },
		{  0.5f, -0.5f, -0.5f }
	},
	// Left
	{
		{ -0.5f,  0.5f, -0.5f },
		{ -0.5f,  0.5f,  0.5f },
		{ -0.5f, -0.5f,  0.5f },
		{ -0.5f, -0.5f, -0.5f }
	},
	// Right
	{
		{  0.5f,  0.5f,  0.5f },
		{  0.5f,  0.5f, -0.5f },
		{  0.5f, -0.5f, -0.5f },
		{  0.5f, -0.5f,  0.5f }
	},
	// Top
	{
		{ -0.5f,  0.5f, -0.5f },
		{  0.5f,  0.5f, -0.5f },
		{  0.5f,  0.5f,  0.5f },
		{ -0.5f,  0.5f,  0.5f }
	},
	// Bottom
	{
		{ -0.5f, -0.5f,  0.5f },
		{  0.5f, -0.5f,  0.5f },
		{  0.5f, -0.5f, -0.5f },
		{ -0.5f, -0.5f, -0.5f }
	}
};

FaceDataRaw faceDataRaw = {
	.faces = {
		.keys = {
			BLOCK_FACE_FRONT,
			BLOCK_FACE_BACK,
			BLOCK_FACE_LEFT,
			BLOCK_FACE_RIGHT,
			BLOCK_FACE_TOP,
			BLOCK_FACE_BOTTOM
		},
		.values = rawVertexData
	}
};
