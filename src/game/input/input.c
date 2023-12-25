#include <GLFW/glfw3.h>
#include <cglm/vec3.h>
#include "../input/input.h"
#include "../global.h"
#include "../types.h"

static void updateKeyState(u8 currentState, KeyState* keyState) {
	if (currentState) {
		if (*keyState > 0) {
			*keyState = KS_HELD;
		} else {
			*keyState = KS_PRESSED;
		}
	} else {
		*keyState = KS_RELEASED;
	}
}

static const f32 defaultSense = 0.04f;
static f32 sensitivity = defaultSense;
static bool firstMouse = true;
static f32 lastX = 1280.0f / 2.0f;
static f32 lastY = 720.0f / 2.0f;

void keyCallback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods) {
	for (u32 i = 0; i < sizeof(global.config.keybinds) / sizeof(global.config.keybinds[0]); i++) {
		if (key == global.config.keybinds[i]) {
			updateKeyState(action, &global.input.key[i]);
		}
	}
}

void cursorCallback(GLFWwindow* window, f64 xpos, f64 ypos);

void cursorCallback(GLFWwindow* window, f64 xposIn, f64 yposIn) {
	f32 xpos = (f32)xposIn;
	f32 ypos = (f32)yposIn;

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	f32 xoffset = xpos - lastX;
	f32 yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	global.camera.yaw += xoffset;
	global.camera.pitch += yoffset;
	if (global.camera.pitch > 89.0f)
		global.camera.pitch = 89.0f;
	if (global.camera.pitch < -89.0f)
		global.camera.pitch = -89.0f;

	global.camera.front[0] = cosf(glm_rad(global.camera.yaw)) * cosf(glm_rad(global.camera.pitch));
	global.camera.front[1] = sinf(glm_rad(global.camera.pitch));
	global.camera.front[2] = sinf(glm_rad(global.camera.yaw)) * cosf(glm_rad(global.camera.pitch));

}
