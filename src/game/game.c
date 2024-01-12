#include <GLFW/glfw3.h>
#include "renderer.h"
#include "input.h"
#include "config.h"
#include "time.h"
#include "camera.h"

// Main game function
void gameRun(void) {

	// Run all init functions
	renderInit();
	configInit();
	timeInit();
	cameraInit();
	inputInit();

	// Main game loop
	while (!glfwWindowShouldClose(renderer.window)) {

		// Main game calls
		renderBegin();
		cameraUpdate();
		renderMain();
		renderEnd();
		timeUpdate();
	}

	// Delete buffers, shaders and more, and terminate GLFW
	renderTerminate();
}
