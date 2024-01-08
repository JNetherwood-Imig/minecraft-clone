#pragma once

#include "../types.h"

typedef struct shader {
	u32 id;
} Shader;

typedef struct shaders {
    Shader shaderDefault;
} Shaders;

extern Shaders shaders;

Shader shaderCreate(const char* vertexShaderPath, const char* fragmentShaderPath);
void shaderBind(Shader* shader);
void shaderUnbind(void);
void shaderDelete(Shader* shader);

