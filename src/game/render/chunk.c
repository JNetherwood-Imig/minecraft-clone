#include "chunk.h"
#include "block.h"
#include "block_data.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "texture.h"
#include "../../include/glad/glad.h"
#include "../../include/cglm/struct.h"
#define FNL_IMPL
#include "../../include/FastNoiseLite.h"

// Function to append face data from a block to the chunk mesh
static void appendFaceData(Chunk* chunk, FaceData data) {

	// Loop through each vertex and uv
	for (int i = 0; i < 4; i++) {
		// Add verticies
		chunk->vertices[chunk->info.vertexCount]  = data.vertices[i];
		// Add uvs and incrament vertex count
		chunk->uvs[chunk->info.vertexCount++] = data.uvs[i];
	}
	// Incrament face counter
	chunk->info.faceCount++;
}

// Function to append indices to chunk mesh
static void appendIndices(Chunk* chunk) {
	// Loop through each face in chunk and add indices
	for (int i = 0; i < chunk->info.faceCount; i++) {
		chunk->indices[chunk->info.indexCount++] = 0 + chunk->info.uniqueIndexCount;
		chunk->indices[chunk->info.indexCount++] = 1 + chunk->info.uniqueIndexCount;
		chunk->indices[chunk->info.indexCount++] = 3 + chunk->info.uniqueIndexCount;
		chunk->indices[chunk->info.indexCount++] = 1 + chunk->info.uniqueIndexCount;
		chunk->indices[chunk->info.indexCount++] = 2 + chunk->info.uniqueIndexCount;
		chunk->indices[chunk->info.indexCount++] = 3 + chunk->info.uniqueIndexCount;

		// Incrament unique index count by 4 which determines the value of the index
		chunk->info.uniqueIndexCount += 4;
	}
}

// Return a heightmap struct generated using FastNoiseLite
static Heightmap generateChunk() {
	// Create and configure noise state
	fnl_state noise = fnlCreateState();
	noise.noise_type = FNL_NOISE_OPENSIMPLEX2;

	// Set some hightmap attributes
	Heightmap heightmap = {
		.heightVariation = 8,
		.minHeight = 4
	};

	// Gather noise data
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++) 
		{
			heightmap.data[x][y] = heightmap.minHeight + (heightmap.heightVariation * fnlGetNoise2D(&noise, x, y));
		}
	}

	return heightmap;
}

// Function to generate all blocks in a chunk
static void generateBlocks(Chunk* chunk) {
	
	// Loop through all x rows in chunk
	for (int x = 0; x < CHUNK_SIZE; x++) {
		// Loop through all z positions in x row
		for (int z = 0; z < CHUNK_SIZE; z++) {
			// Loop through all y positions in x, z column
			for (int y = 0; y < CHUNK_HEIGHT; y++) {
				// Define column height using x, z, position in hightmap
				f32 columnHeight = chunk->heightmap.data[x][z];
				// Generate grass blocks on top layer
				if (y < columnHeight && y >= columnHeight-1) {
					chunk->blocks[x][y][z] = createBlock((vec3s){{x, y, z}}, BLOCK_TYPE_GRASS);
				// Generate dirt on next 2 layers
				} else if (y < columnHeight-1 && y >= columnHeight-3) {
					chunk->blocks[x][y][z] = createBlock((vec3s){{x, y, z}}, BLOCK_TYPE_DIRT);
				// Fill rest of the way down with stone
				} else if (y < columnHeight-3) {
					chunk->blocks[x][y][z] = createBlock((vec3s){{x, y, z}}, BLOCK_TYPE_STONE);
				// Everything else is made empty
				} else {
					chunk->blocks[x][y][z] = createBlock((vec3s){{x, y, z}}, BLOCK_TYPE_EMPTY);
				}
			}
		}
	}
}

// Function to generate faces using the blocks in the chunk
static void generateFaces(Chunk* chunk) {
	// Loop through positions in chunk below the heightmap
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int y = 0; y < chunk->heightmap.data[x][z]; y++) {
				// Left faces: add if block to the left is empty or is farthest left in chunk
				if (x > 0) {
					if (chunk->blocks[x-1][y][z].type == BLOCK_TYPE_EMPTY) {
						appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_LEFT]);
					}
				} else {
					appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_LEFT]);
				}
				// Right faces: add if block to the right is empty or if is farthest right in chunk
				if (x < CHUNK_SIZE-1) {
					if (chunk->blocks[x][y][z].type == BLOCK_TYPE_EMPTY) {
						appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_RIGHT]);
					}
				} else {
					appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_RIGHT]);
				}
				// Front faces: add if block in front is empty or if is farthest forward in chunk
				if (z < CHUNK_SIZE-1) {
					if (chunk->blocks[x][y][z].type == BLOCK_TYPE_EMPTY) {
						appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_FRONT]);
					}
				} else {
					appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_FRONT]);
				}
				// Back faces: add if block behind is empty or if is farthest back in chunk
				if (z > 0) {
					if (chunk->blocks[x][y][z-1].type == BLOCK_TYPE_EMPTY) {
						appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_BACK]);
					}
				} else {
					appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_BACK]);
				}
				// Top faces: add if block above is empty or if is top in chunk
				if (y < chunk->heightmap.data[x][z]-1) {
					if (chunk->blocks[x][y][z].type == BLOCK_TYPE_EMPTY) {
						appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_TOP]);
					}
				} else {
					appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_TOP]);
				}
				// Bottom faces: add if block below is empty or if is lowest in chunk
				if (y > 0) {
					if (chunk->blocks[x][y-1][z].type == BLOCK_TYPE_EMPTY) {
						appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_BOTTOM]);
					}
				} else {
					appendFaceData(chunk, chunk->blocks[x][y][z].faces[BLOCK_FACE_BOTTOM]);
				}
			}
		}
	}
	// After all faces have been added,
	// indicies can be added using the face count
	appendIndices(chunk);
}

// Function to build the chunk buffers for OpenGL to render
static void buildChunk(Chunk* chunk) {

	// Create a vertex array object for the chunk
	vaoCreate(&chunk->vao);

	// Create vertex buffer for chunk vertices
	vboCreate(&chunk->vertexVbo, &chunk->vertices, sizeof(chunk->vertices), false);
	vaoAttrib(0, 3, 0, 0);
	// Create vertex buffer for chunk uvs
	vboCreate(&chunk->uvVbo, &chunk->uvs, sizeof(chunk->uvs), false);
	vaoAttrib(1, 2, 0, 0);
	// Create element buffer for chunk vertices
	eboCreate(&chunk->ebo, &chunk->indices, sizeof(chunk->indices), false);

	// Unbind vao and vbo
	vboUnbind();
	vaoUnbind();
}

// Function to return a chunk struct using a given world position
Chunk createChunk(vec3s position) {
	Chunk self = {
		.position = position,
		.heightmap = generateChunk(),
		.info = {0}
	};

	// Generate chunk data
	generateBlocks(&self);
	generateFaces(&self);
	buildChunk(&self);

	return self;
}

// Function to render a chunk mesh
void renderChunk(Chunk* chunk) {
	// Bind shader and set a shader uniform for the model matrix
	shaderBind(&shaders.shaderDefault);
	shaderUniform(&shaders.shaderDefault,
		"model",
		glms_translate(glms_mat4_identity(), chunk->position).raw[0]);
	// Bind chunk vao and texture
	vaoBind(&chunk->vao);
	textureBind(textures.altas.id);

	// Draw elements from chunk indices
	glDrawElements(GL_TRIANGLES, chunk->info.indexCount, GL_UNSIGNED_INT, 0);
}

