#pragma once

#include <GLFW/glfw3.h>
#include "util/types.h"

typedef struct renderer {
	u32 width;
	u32 height;
	GLFWwindow* window;
} Renderer;

extern Renderer renderer;

void renderInit(void);
void renderBegin(void);
void renderMain(void);
void renderEnd(void);
void renderClean(void);
