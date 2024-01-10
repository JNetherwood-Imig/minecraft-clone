#include "block.h"
#include "block_data.h"
#include <cglm/cglm.h>
#include <cglm/struct.h>
#include <cglm/struct/vec3.h>
#include <string.h>

vec2s defaultUvs[4] = {
	{{ 0.0f, 0.0f }},
	{{ 1.0f, 0.0f }},
	{{ 1.0f, 1.0f }},
	{{ 0.0f, 1.0f }}
};

static void addTransformedVertices(vec3s dest[4], FaceDataRaw* faceDataRaw, vec3s position) {
	for (int i = 0; i < 4; i++) {
		dest[i] = glms_vec3_add(*(vec3s*)&faceDataRaw->faces.values[0][i], position);
	}
}

Block createBlock(vec3s position) {


	Block block = { .postiton = position };
	
	
	for (int i = 0; i < 6; i++) {
		addTransformedVertices(block.faces[i].vertices, &faceDataRaw, block.postiton);
		memcpy(block.faces[i].uvs, &defaultUvs[0], sizeof(vec2s));
	}

	return block;
}

