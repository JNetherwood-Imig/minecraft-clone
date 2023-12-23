#include <cglm/cglm.h>
#include <cglm/vec3.h>
#include <string.h>
#include "../global.h"

static vec3 cameraPosition = { 0.0f, 0.0f,  3.0f };
static vec3 cameraFront    = { 0.0f, 0.0f, -1.0f };
static vec3 cameraUp       = { 0.0f, 1.0f,  0.0f };

void cameraInit(void) {
	global.camera.speed =  3.0f;
	global.camera.fov   = 45.0f;
	memcpy(global.camera.position, cameraPosition, sizeof(cameraPosition));
	memcpy(global.camera.front, cameraFront, sizeof(cameraFront));
	memcpy(global.camera.up, cameraUp, sizeof(cameraUp));
}

void cameraUpdate(void) {
	glm_vec3_scale(global.camera.front, global.camera.speed * global.time.delta, global.camera.forward);
	glm_cross(global.camera.front, global.camera.up, global.camera.right);
	glm_normalize(global.camera.right);
	glm_vec3_scale(global.camera.right, global.camera.speed * global.time.delta, global.camera.right);
	vec3 scaledUp;
	glm_vec3_scale(global.camera.up, global.camera.speed * global.time.delta, scaledUp);
	if (global.input.key[INPUT_KEY_FORWARD] == KS_PRESSED || global.input.key[INPUT_KEY_FORWARD] == KS_HELD) {
		glm_vec3_add(global.camera.position, global.camera.forward, global.camera.position);
	}

	if (global.input.key[INPUT_KEY_BACKWARD] == KS_PRESSED || global.input.key[INPUT_KEY_BACKWARD] == KS_HELD) {
		glm_vec3_sub(global.camera.position, global.camera.forward, global.camera.position);
	}

	if (global.input.key[INPUT_KEY_LEFT] == KS_PRESSED || global.input.key[INPUT_KEY_LEFT] == KS_HELD) {
		glm_vec3_sub(global.camera.position, global.camera.right, global.camera.position);
	}

	if (global.input.key[INPUT_KEY_RIGHT] == KS_PRESSED || global.input.key[INPUT_KEY_RIGHT] == KS_HELD) {
		glm_vec3_add(global.camera.position, global.camera.right, global.camera.position);
	}
	
	if (global.input.key[INPUT_KEY_DOWN] == KS_PRESSED || global.input.key[INPUT_KEY_DOWN] == KS_HELD) {
		glm_vec3_sub(global.camera.position, scaledUp, global.camera.position);
	}

	if (global.input.key[INPUT_KEY_UP] == KS_PRESSED || global.input.key[INPUT_KEY_UP] == KS_HELD) {
		glm_vec3_add(global.camera.position, scaledUp, global.camera.position);
	}
}

