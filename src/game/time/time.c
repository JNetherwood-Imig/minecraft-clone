#include <GLFW/glfw3.h>
#include "time.h"
#include "../global.h"

void timeInit(void) {
	global.time.now = 0;
	global.time.last = 0;
	global.time.delta = 0;
}

void timeUpdate(void) {
	global.time.now = glfwGetTime();
	global.time.delta = global.time.now - global.time.last;
	// global.time.delta = 1.0f / 165.0f;
	global.time.last = global.time.now;
}
