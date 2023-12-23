#pragma once

#include <GLFW/glfw3.h>
#include <cglm/types.h>
#include "../types.h"

typedef struct renderStateInternal {
	mat4 model;
	mat4 view;
	mat4 projection;
	u32 shaderDefault;
	u32 texture;
	u32 cubeVao;
	u32 cubeVbo;
	u32 cubeEbo;
} RenderStateInternal;

GLFWwindow* renderInitWindow(u32 width, u32 height);
void renderInitCube(RenderStateInternal* state);
void renderInitShaders(RenderStateInternal* state);
void renderInitTextures(RenderStateInternal* state);
u32 renderCreateShader(const char* vertexShaderPath, const char* fragmentShaderPath);
