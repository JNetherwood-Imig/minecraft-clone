#pragma once

#include <GLFW/glfw3.h>
#include <cglm/types-struct.h>
#include "util/types.h"

struct RendererState {
	mat4s view;
	mat4s projection;
};

typedef struct renderer {
	u32 width;
	u32 height;
	GLFWwindow* window;
	struct RendererState state;
} Renderer;

extern Renderer renderer;

void renderInit(void);
void renderBegin(void);
void renderMain(void);
void renderEnd(void);
void renderClean(void);
