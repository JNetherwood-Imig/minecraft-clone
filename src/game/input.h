#pragma once

#include <GLFW/glfw3.h>
#include "util/types.h"

// Define input keys
typedef enum InputKey {
	INPUT_KEY_FORWARD,
	INPUT_KEY_BACKWARD,
	INPUT_KEY_LEFT,
	INPUT_KEY_RIGHT,
	INPUT_KEY_UP,
	INPUT_KEY_DOWN,
	INPUT_KEY_ESCAPE,
	INPUT_KEY_ENUM_LENGTH
} InputKey;

// Define key states
typedef enum KeyState {
	KS_RELEASED,
	KS_PRESSED,
	KS_HELD
} KeyState;

// Define input state struct with array of key states,
// providing a key state for every input key
typedef struct InputState {
	KeyState key[INPUT_KEY_ENUM_LENGTH];
} InputState;

// Create external input state object
extern InputState input;

// Define function prototypes for inputInit and glfw input callbacks
void inputInit(void);
void keyCallback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods);
void cursorCallback(GLFWwindow* window, f64 xposIn, f64 yposIn);
