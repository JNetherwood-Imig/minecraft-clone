#pragma once

#include "../types.h"

typedef struct blockType {
    const char* name;
    u8 row;
    u8 collumn;
    f32 vertices[120];
    u32 indices[36];
} BlockType;

typedef struct block {
    u32 vao;
    u32 vbo;
    u32 ebo;
} Block;

BlockType blockInit(const char* name, u8 row, u8 collumn);
Block blockCreate();