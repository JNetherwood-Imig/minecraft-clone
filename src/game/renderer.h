#pragma once

#include <GLFW/glfw3.h>
#include "../include/cglm/types-struct.h"
#include "util/types.h"

// Define renderer state struct with view and projection matricies
// making use of the cglm struct api
struct RendererState {
	mat4s view;
	mat4s projection;
};

// Define main renderer struct with window information and a GLFWwindow*,
// as well as a state struct
typedef struct Renderer {
	u32 width;
	u32 height;
	GLFWwindow* window;
	struct RendererState state;
} Renderer;

// Create external renderer object
extern Renderer renderer;

// Define function prototypes for stages of the render loop
void renderInit(void);
void renderBegin(void);
void renderMain(void);
void renderEnd(void);
void renderTerminate(void);
