#include <GLFW/glfw3.h>
#include "../time.h"

// Initialize empty time state
TimeState time = {0};

// Initialize all values to 0
void timeInit(void) {
	time.now = 0;
	time.last = 0;
	time.delta = 0;
}

// Updata time state values
void timeUpdate(void) {
	// Update current time using glfwGetTime (stored in seconds)
	time.now = glfwGetTime();
	// Update time delta to be time between frames
	time.delta = time.now - time.last;
	// Update time.last to current time
	time.last = time.now;
}
