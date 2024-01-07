#pragma once

#include <GLFW/glfw3.h>
#include <cglm/types.h>
#include "types.h"

typedef struct renderState {
	u32 width;
	u32 height;
	GLFWwindow *window;
} RenderState;

void renderInit(void);
void renderBegin(void);
void renderMain(void);
void renderEnd(void);
void renderCube(vec3 position);
void renderCameraUpdate(void);
