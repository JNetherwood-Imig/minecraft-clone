#include "block.h"
#include "block_data.h"
#include <cglm/struct.h>
#include <cglm/struct/vec3.h>
#include <string.h>

vec2s defaultUvs[4] = {
	{ 0.0f, 0.0f },
	{ 1.0f, 0.0f },
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f }
};

Block createBlock(vec3s position) {


	Block block = { .postiton = position };
	
	
	for (int i = 0; i < 6; i++) {
		addTransformedVertices(block.faces[i].vertices, faceDataRaw.faces.values[i], block.postiton);
		memcpy(block.faces[i].uvs, &defaultUvs[i], sizeof(vec2s));
	}

	return block;
}

void addTransformedVertices(vec3s dest[4], vec3s vertices[4], vec3s position) {
	for (int i = 0; i < 4; i++) {
		dest[i] = glms_vec3_add(vertices[i], position);
	}
}

