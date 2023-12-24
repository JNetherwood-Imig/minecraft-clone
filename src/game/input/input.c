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

static const f32 defaultSense = 0.05f;
static f32 sensitivity = defaultSense;
static f32 yaw = -90.0f;
static f32 pitch = 0.0f;
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

	yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	vec3 front;
	front[0] = cosf(glm_rad(yaw)) * cosf(glm_rad(pitch));
	front[1] = 0.0f;
	front[2] = sinf(glm_rad(yaw)) * cosf(glm_rad(pitch));
	glm_normalize(front);
	vec3 view;
	view[0] = cosf(glm_rad(yaw)) * cosf(glm_rad(pitch));
	view[1] = sinf(glm_rad(pitch));
	view[2] = sinf(glm_rad(yaw)) * cosf(glm_rad(pitch));
	glm_normalize(view);
	glm_vec3_copy(front, global.camera.front);
	glm_vec3_copy(view, global.camera.view);
}
