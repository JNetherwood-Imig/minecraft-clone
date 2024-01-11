#include "block.h"
#include "block_data.h"
#include <cglm/struct.h>

static void addTransformedVertices(FaceData* destination, vec3s* vertices, vec3s position) {
	for (int i = 0; i < 4; i++) {
		destination->vertices[i] = glms_vec3_add(vertices[i], position);
	}
}

Block createBlock(vec3s position) {

	Block self = { .postiton = position };

	for (int i = 0; i < 6; i++) {
		addTransformedVertices(&self.faces[i], vertexData[i], self.postiton);
		self.faces[i].uvs = uvData;
	}

	return self;
}
