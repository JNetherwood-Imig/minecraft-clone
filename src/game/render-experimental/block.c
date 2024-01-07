#include <glad/glad.h>
#include "block.h"
#include "../types.h"

static const u32 textureSize  = 16;
static const u32 atlasSize    = 128;
static const f32 atlasTextureSize = 1.0f / (atlasSize / textureSize);

BlockType blockInit(const char* name, u8 row, u8 collumn) {
    BlockType block;

    block.row = row;
    block.collumn = collumn;
    
    f32 xOffsetClose = block.collumn * atlasTextureSize;
    f32 xOffsetFar = (block.collumn + 1) * atlasTextureSize;
    f32 yOffsetClose = block.row * atlasTextureSize;
    f32 yOffsetFar = (block.collumn + 1) * atlasTextureSize;
    f32 vertices[] = {
		// x      y      z      Tx    Ty
		-0.5f,  0.5f,  0.5f, xOffsetClose, yOffsetClose,
         0.5f,  0.5f,  0.5f, xOffsetFar,   yOffsetClose,
         0.5f, -0.5f,  0.5f, xOffsetFar,   yOffsetFar,
        -0.5f, -0.5f,  0.5f, xOffsetClose, yOffsetFar,

         0.5f,  0.5f, -0.5f, xOffsetClose, yOffsetClose,
        -0.5f,  0.5f, -0.5f, xOffsetFar,   yOffsetClose,
        -0.5f, -0.5f, -0.5f, xOffsetFar,   yOffsetFar,
         0.5f, -0.5f, -0.5f, xOffsetClose, yOffsetFar,

        -0.5f,  0.5f, -0.5f, xOffsetClose, yOffsetClose,
        -0.5f,  0.5f,  0.5f, xOffsetFar,   yOffsetClose,
        -0.5f, -0.5f,  0.5f, xOffsetFar,   yOffsetFar,
        -0.5f, -0.5f, -0.5f, xOffsetClose, yOffsetFar,

         0.5f,  0.5f,  0.5f, xOffsetClose, yOffsetClose,
         0.5f,  0.5f, -0.5f, xOffsetFar,   yOffsetClose,
         0.5f, -0.5f, -0.5f, xOffsetFar,   yOffsetFar,
         0.5f, -0.5f,  0.5f, xOffsetClose, yOffsetFar,

        -0.5f,  0.5f, -0.5f, xOffsetClose, yOffsetClose,
         0.5f,  0.5f, -0.5f, xOffsetFar,   yOffsetClose,
         0.5f,  0.5f,  0.5f, xOffsetFar,   yOffsetFar,
        -0.5f,  0.5f,  0.5f, xOffsetClose, yOffsetFar,

        -0.5f, -0.5f,  0.5f, xOffsetClose, yOffsetClose,
         0.5f, -0.5f,  0.5f, xOffsetFar,   yOffsetClose,
         0.5f, -0.5f, -0.5f, xOffsetFar,   yOffsetFar,
        -0.5f, -0.5f, -0.5f, xOffsetClose, yOffsetFar
	};
    memcpy(block.vertices, vertices, sizeof(vertices) / sizeof(f32));
    
    u32 indices[] = {
        0, 1, 3,
        1, 2, 3,

        4, 5, 7,
        5, 6, 7,

        8, 9, 11,
        9, 10, 11,

        12, 13, 15,
        13, 14, 15,

        16, 17, 19,
        17, 18, 19,

        20, 21, 23,
        21, 22, 23
    };
    memcpy(block.indices, indices, sizeof(indices) / sizeof(u32));
}

Block blockCreate(BlockType* type) {
    Block block;

    glGenVertexArrays(1, &block.vao);
	glBindVertexArray(block.vao);

	glGenBuffers(1, &block.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, block.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(type->vertices), type->vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &block.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, block.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(type->indices), type->indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)(3 * sizeof(f32)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

    return block;
}