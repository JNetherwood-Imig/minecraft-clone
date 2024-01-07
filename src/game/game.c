#include <GLFW/glfw3.h>
#include "global.h"
#include "render.h"
#include "input.h"
#include "config.h"
#include "time.h"
#include "camera.h"

static vec3 position = {0.0f, 0.0f, 0.0f};

static void inputHandle(void) {
	if (input.key[INPUT_KEY_ESCAPE] == KS_PRESSED || input.key[INPUT_KEY_ESCAPE] == KS_HELD) {
		glfwSetWindowShouldClose(global.render.window, GLFW_TRUE);
	}
}

void gameRun(void) {

	renderInit();
	configInit();
	timeInit();
	cameraInit();

	glfwSetInputMode(global.render.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(global.render.window, keyCallback);
	glfwSetCursorPosCallback(global.render.window, cursorCallback);

	while (!glfwWindowShouldClose(global.render.window)) {

		renderBegin();
		inputHandle();
		cameraUpdate();
		renderCameraUpdate();
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				for (int k = 0; k < 4; k++) {
					position[0] = i;
					position[1] = k;
					position[2] = j;
					renderCube(position);
				}
			}
		}
		renderEnd();
		timeUpdate();
	}

	glfwTerminate();
}
