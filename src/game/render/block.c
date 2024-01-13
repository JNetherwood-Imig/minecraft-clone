#include "block.h"
#include "block_data.h"
#include "texture.h"
#include "../../include/cglm/struct.h"

// Texture atlas information
// Texture atlas size (pixels)
static const u32 atlasSize  = 256;
// Size of each block texture (pixels)
static const u32 textureSize = 16;
// Fraction of atlas size occupied by each texture as a decimal
static f32 atlasTextureScale = 1.0f / (atlasSize / textureSize);

// Function to transform the default block vertices to the block position
//  and add them to the block face data
static void addTransformedVertices(FaceData* destination, vec3s* vertices, vec3s position) {
	// Loop through each vertex in face
	for (int i = 0; i < 4; i++) {
		// Transform vertex to position and add it to block face
		destination->vertices[i] = glms_vec3_add(vertices[i], position);
	}
}

// Add correct vertices for block face to block face data
static void addUvs(FaceData* destination, FaceTypeInfo* typeInfo) {
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

// Function to return a block struct with correct vertex data
// to be added to the chunk mesh
Block createBlock(vec3s position, BlockType type) {

	// Create new block
	Block self = {
		.postiton = position,
		.blockTypeInfo = blockTypeInfo[type],
		.type = type
	};

	// If the type isn't BLOCK_TYPE_EMPTY, add vertices and uvs to block face data
	if (type != BLOCK_TYPE_EMPTY) {
		// Loop through each face
		for (int face = 0; face < 6; face++) {
			addTransformedVertices(&self.faces[face], vertexData[face], self.postiton);
			addUvs(&self.faces[face], faceTypeInfo[self.blockTypeInfo->faceType[face]]);
		}
	}

	return self;
}
