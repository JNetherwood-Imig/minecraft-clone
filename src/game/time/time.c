#include <GLFW/glfw3.h>
#include "../time.h"

TimeState time = {0};

void timeInit(void) {
	time.now = 0;
	time.last = 0;
	time.delta = 0;
}

void timeUpdate(void) {
	time.now = glfwGetTime();
	time.delta = time.now - time.last;
	time.last = time.now;
}
