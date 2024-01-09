#include "chunk.h"
#include "block.h"
#include "block_data.h"

Chunk createChunk(vec3s position) {
	Chunk chunk = { .position = position };
	return chunk;
}

void genChunk(Chunk* chunk);

void genBlocks(Chunk* chunk) {
	for (int i = 0; i < 3; i++) {
		Block block = createBlock((vec3s){i, 0, 0});
		FaceData frontFaceData = block.faces[BLOCK_FACE_FRONT];
		Node* frontVerts = addNode(&chunk->vertices, &frontFaceData.vertices);
		Node* frontUvs = addNode(&chunk->uvs, &frontFaceData.uvs);
	}
}

void buildChunk(Chunk* chunk);

void renderChunk(Chunk* chunk, Shader shader);

