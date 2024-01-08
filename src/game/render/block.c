#include <glad/glad.h>
#include <cglm/cglm.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "block.h"
#include "shader.h"

static const f32 blockSize = 0.5f;
static const u8 atlasSize = 128;
static const u8 textureResolution = 16;
static const u8 atlasTextureDimension = atlasSize / textureResolution;
static const f32 atlasOffset = 1.0f / atlasTextureDimension;

void generateTextureOffset(BlockType* block) {
	block->xOffsetClose = atlasOffset * block->atlasRow;
	block->xOffsetFar   = atlasOffset * block->atlasRow + 1;
	block->yOffsetClose = atlasOffset * block->atlasCollumn;
	block->yOffsetFar   = atlasOffset * block->atlasCollumn + 1;
}

static u32 texture;

void generateTexture(void) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	i32 width, height, nrChannels;
	unsigned char* data = stbi_load("assets/texture-atlas.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		printf("Failed to load texture\n");
	}
	stbi_image_free(data);
}

Block createBlock(BlockType* type) {
	Block block;
	generateTextureOffset(type);
	f32 vertices[] = {
		-blockSize,  blockSize,  blockSize, type->xOffsetClose, type->yOffsetFar,
		-blockSize, -blockSize,  blockSize, type->xOffsetClose, type->yOffsetClose, 
		 blockSize, -blockSize,  blockSize, type->xOffsetFar,   type->yOffsetClose,
		 blockSize, -blockSize,  blockSize, type->xOffsetFar,   type->yOffsetClose,
		 blockSize,  blockSize,  blockSize, type->xOffsetFar,   type->yOffsetFar,
		-blockSize,  blockSize, -blockSize, type->xOffsetClose, type->yOffsetFar,
		-blockSize, -blockSize, -blockSize, type->xOffsetClose, type->yOffsetClose,
		 blockSize, -blockSize, -blockSize, type->xOffsetFar,   type->yOffsetClose,
		 blockSize,  blockSize, -blockSize, type->xOffsetFar,   type->yOffsetFar,
	};
	// f32 vertices[] = {
	// 	// x      y      z      Tx    Ty
	// 	-0.3f, -0.3f, -0.3f,  0.0f, 0.0f,
	// 	 0.3f, -0.3f, -0.3f,  1.0f, 0.0f,
	// 	 0.3f,  0.3f, -0.3f,  1.0f, 1.0f,
	// 	 0.3f,  0.3f, -0.3f,  1.0f, 1.0f,
	// 	-0.3f,  0.3f, -0.3f,  0.0f, 1.0f,
	// 	-0.3f, -0.3f, -0.3f,  0.0f, 0.0f,
	//
	// 	-0.3f, -0.3f,  0.3f,  0.0f, 0.0f,
	// 	 0.3f, -0.3f,  0.3f,  1.0f, 0.0f,
	// 	 0.3f,  0.3f,  0.3f,  1.0f, 1.0f,
	// 	 0.3f,  0.3f,  0.3f,  1.0f, 1.0f,
	// 	-0.3f,  0.3f,  0.3f,  0.0f, 1.0f,
	// 	-0.3f, -0.3f,  0.3f,  0.0f, 0.0f,
	//
	// 	-0.3f,  0.3f,  0.3f,  1.0f, 0.0f,
	// 	-0.3f,  0.3f, -0.3f,  1.0f, 1.0f,
	// 	-0.3f, -0.3f, -0.3f,  0.0f, 1.0f,
	// 	-0.3f, -0.3f, -0.3f,  0.0f, 1.0f,
	// 	-0.3f, -0.3f,  0.3f,  0.0f, 0.0f,
	// 	-0.3f,  0.3f,  0.3f,  1.0f, 0.0f,
	//
	// 	 0.3f,  0.3f,  0.3f,  1.0f, 0.0f,
	// 	 0.3f,  0.3f, -0.3f,  1.0f, 1.0f,
	// 	 0.3f, -0.3f, -0.3f,  0.0f, 1.0f,
	// 	 0.3f, -0.3f, -0.3f,  0.0f, 1.0f,
	// 	 0.3f, -0.3f,  0.3f,  0.0f, 0.0f,
	// 	 0.3f,  0.3f,  0.3f,  1.0f, 0.0f,
	//
	// 	-0.3f, -0.3f, -0.3f,  0.0f, 1.0f,
	// 	 0.3f, -0.3f, -0.3f,  1.0f, 1.0f,
	// 	 0.3f, -0.3f,  0.3f,  1.0f, 0.0f,
	// 	 0.3f, -0.3f,  0.3f,  1.0f, 0.0f,
	// 	-0.3f, -0.3f,  0.3f,  0.0f, 0.0f,
	// 	-0.3f, -0.3f, -0.3f,  0.0f, 1.0f,
	//
	// 	-0.3f,  0.3f, -0.3f,  0.0f, 1.0f,
	// 	 0.3f,  0.3f, -0.3f,  1.0f, 1.0f,
	// 	 0.3f,  0.3f,  0.3f,  1.0f, 0.0f,
	// 	 0.3f,  0.3f,  0.3f,  1.0f, 0.0f,
	// 	-0.3f,  0.3f,  0.3f,  0.0f, 0.0f,
	// 	-0.3f,  0.3f, -0.3f,  0.0f, 1.0f
	// };

	u32 indices[] = {
		0, 1, 2, 3,
		4, 5, 6, 7,
		0, 1, 4, 5,
		2, 3, 6, 7,
		0, 3, 4, 7,
		1, 2, 5, 8
	};

	glGenVertexArrays(1, &block.vao);
	glBindVertexArray(block.vao);

	glGenBuffers(1, &block.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, block.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &block.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, block.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)(3 * sizeof(f32)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	block.type = *type;
	return block;
}

void renderBlock(Block* block, vec3 position) {
	
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(block->vao);

	glm_mat4_identity(block->model);
	glm_translate(block->model, position);
	
	glUniformMatrix4fv(glGetUniformLocation(shaderDefault.id, "model"), 1, GL_FALSE, block->model[0]);

	// glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);

}
