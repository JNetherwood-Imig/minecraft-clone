#pragma once

#include "../types.h"

typedef struct shaders {
    u32 shaderDefault;
} Shaders;

extern Shaders shaders;

u32 shaderCreate(const char* vertexShaderPath, const char* fragmentShaderPath);