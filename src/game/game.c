#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "global.h"
#include "render/render.h"
#include "input/input.h"
#include "config/config.h"
#include "time/time.h"
#include "camera/camera.h"

static vec3 position = {0.0f, 0.0f, 0.0f};

static void inputHandle(void) {
	if (global.input.key[INPUT_KEY_ESCAPE] == KS_PRESSED || global.input.key[INPUT_KEY_ESCAPE] == KS_HELD) {
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
		renderCube(position);
		renderEnd();
		timeUpdate();
	}

	glfwTerminate();
}
