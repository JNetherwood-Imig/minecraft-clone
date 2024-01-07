#pragma once

#include <GLFW/glfw3.h>
#include "types.h"

typedef enum inputKey {
	INPUT_KEY_FORWARD,
	INPUT_KEY_BACKWARD,
	INPUT_KEY_LEFT,
	INPUT_KEY_RIGHT,
	INPUT_KEY_UP,
	INPUT_KEY_DOWN,
	INPUT_KEY_ESCAPE
} InputKey;

typedef enum keyState {
	KS_RELEASED,
	KS_PRESSED,
	KS_HELD
} KeyState;

typedef struct inputState {
	KeyState key[7];
} InputState;

extern InputState input;

void keyCallback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods);
void cursorCallback(GLFWwindow* window, f64 xpos, f64 ypos);
