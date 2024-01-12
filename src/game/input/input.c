#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/vec3.h>
#include "../input.h"
#include "../config.h"
#include "../camera.h"
#include "../renderer.h"
#include "../util/types.h"

// Initialize empty input state
InputState input = {0};

// Function to update the state of keys to KS_RELEASED, KS_PRESSED, or KS_HELD
static void updateKeyState(u8 currentState, KeyState* keyState) {
	// If the action registered by the key callback is GLFW_PRESS
	if (currentState) {
		// Check if the state of the key is KS_PRESSED or KS_HELD
		if (*keyState > 0) {
			// Update the key state to KS_HELD
			*keyState = KS_HELD;
		} else {
			// If the key was not already pressed,
			// update the key state to KS_PRESSED
			*keyState = KS_PRESSED;
		}
	} else {
		// If the registered action was GLFW_RELEASE,
		// set the key state to KS_RELEASED
		*keyState = KS_RELEASED;
	}
}

// Initialize key callback functions and cursor mode
void inputInit(void) {
	glfwSetKeyCallback(renderer.window, keyCallback);
	glfwSetCursorPosCallback(renderer.window, cursorCallback);
	glfwSetInputMode(renderer.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

// Initialize variables for mouse input
static const f32 defaultSense = 0.04f; // Arbitrary number
// When zoom is added, there needs to be a separate variable to store the current sensitivity
// so that the camera sensitivity can be lowered while zoomed in
static f32 sensitivity = defaultSense;
// Check if it is the first mouse update
static bool firstMouse = true;
// Initialize mouse position to center of screen
static f32 lastX = 1280.0f / 2.0f;
static f32 lastY = 720.0f / 2.0f;
// Stores if rendering is currently set to wireframe mode for inspecting mesh
static bool wireframe;

// GLFW key callback
void keyCallback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods) {
	// Loops through all elements in keybinds array
	for (u32 i = 0; i < sizeof(config.keybinds) / sizeof(u32); i++) {
		// Checks if currently updated key is element [i] of keybinds
		if (key == config.keybinds[i]) {
			// If it is, update the key state
			updateKeyState(action, &input.key[i]);
		}
	}

	// If 'G' is pressed, toggle wireframe
	if (key == GLFW_KEY_G && action == GLFW_PRESS) {
		// Sets glPolygonMode to either GL_LINE or GL_FILL depending on the wireframe boolean
		glPolygonMode(GL_FRONT_AND_BACK, wireframe? GL_LINE : GL_FILL);
		// Toggles wireframe boolean
		wireframe = !wireframe;
	}

	// Check for escape key event and close window
	if (key == config.keybinds[INPUT_KEY_ESCAPE] && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(renderer.window, GLFW_TRUE);
	}
}

// GLFW cursor callback
void cursorCallback(GLFWwindow* window, f64 xposIn, f64 yposIn) {
	// Casts GLFW-required f64 inputs to more usable f32 values
	f32 xpos = (f32)xposIn;
	f32 ypos = (f32)yposIn;

	// Stops screen from jumping on first mouse movement
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	// Gets offset of current cursor position from last cursor position
	f32 xOffset = xpos - lastX;
	f32 yOffset = lastY - ypos;
	// Updates last cursor position to current cursor position
	lastX = xpos;
	lastY = ypos;
	
	// Scales cursor offset by sensitivity
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	// Updates camera yaw and pitch by scaled offset amounts
	camera.yaw += xOffset;
	camera.pitch += yOffset;
	// Checks if camera pitch is exceeding the acceptable range
	// and stops its movement if it is
	if (camera.pitch > 89.0f)
		camera.pitch = 89.0f;
	if (camera.pitch < -89.0f)
		camera.pitch = -89.0f;

}
