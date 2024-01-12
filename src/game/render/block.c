#include "block.h"
#include "block_data.h"
#include <cglm/struct.h>

static const u32 atlasSize  = 256;
static const u32 textureSize = 16;
static f32 atlasTextureScale = 1.0f / (atlasSize / textureSize);

static void addTransformedVertices(FaceData* destination, vec3s* vertices, vec3s position) {
	for (int i = 0; i < 4; i++) {
		destination->vertices[i] = glms_vec3_add(vertices[i], position);
	}
}

static void addUvs(FaceData* destination, BlockTypeInfo* typeInfo) {
	// Top left
	destination->uvs[0].u = typeInfo->column * atlasTextureScale;
	destination->uvs[0].v = typeInfo->row * atlasTextureScale;
	// Top right
	destination->uvs[1].u = (typeInfo->column+1) * atlasTextureScale;
	destination->uvs[1].v = typeInfo->row * atlasTextureScale;
	// Bottom right
	destination->uvs[2].u = (typeInfo->column+1) * atlasTextureScale;
	destination->uvs[2].v = (typeInfo->row+1) * atlasTextureScale;
	// Bottom left
	destination->uvs[3].u = typeInfo->column * atlasTextureScale;
	destination->uvs[3].v = (typeInfo->row+1) * atlasTextureScale;
}

Block createBlock(vec3s position, BlockType type) {

	Block self = {
		.postiton = position,
		// .atlasInfo = &atlasInfo[type],
		.type = type
	};

	for (int i = 0; i < 6; i++) {
		addTransformedVertices(&self.faces[i], vertexData[i], self.postiton);
		addUvs(&self.faces[i], typeInfo[FACE_TYPE_GRASS_TOP]);
	}

	return self;
}
