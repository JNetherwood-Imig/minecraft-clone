#pragma once

#include "../util/types.h"

// Define shader struct with currently only a program id
typedef struct Shader {
	u32 id;
} Shader;

// Define struct for holding all shaders
// Currently there is only 1 shader,
// but this way more can be easily added
typedef struct Shaders {
    Shader shaderDefault;
} Shaders;

// Create external shaders struct
extern Shaders shaders;

// Define shader utility function prototypes
Shader shaderCreate(const char* vertexShaderPath, const char* fragmentShaderPath);
void shaderBind(Shader* shader);
void shaderUnbind(void);
void shaderDelete(Shader* shader);
void shaderUniform(Shader* shader, const char* uniform, f32* value);
