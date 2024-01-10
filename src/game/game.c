#include <GLFW/glfw3.h>
#include "renderer.h"
#include "input.h"
#include "config.h"
#include "time.h"
#include "camera.h"

static void inputHandle(void) {
	if (input.key[INPUT_KEY_ESCAPE] == KS_PRESSED || input.key[INPUT_KEY_ESCAPE] == KS_HELD) {
		glfwSetWindowShouldClose(renderer.window, GLFW_TRUE);
	}
}

void gameRun(void) {

	renderInit();
	configInit();
	timeInit();
	cameraInit();

	glfwSetInputMode(renderer.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(renderer.window, keyCallback);
	glfwSetCursorPosCallback(renderer.window, cursorCallback);

	while (!glfwWindowShouldClose(renderer.window)) {

		renderBegin();
		inputHandle();
		cameraUpdate();
		renderMain();
		renderEnd();
		timeUpdate();
	}

	// renderClean();
}
