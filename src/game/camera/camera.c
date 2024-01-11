#include <cglm/cglm.h>
#include "../camera.h"
#include "../input.h"
#include "../time.h"

Camera camera = {0};

static vec3 cameraPosition = { 0.0f, 0.0f,  3.0f };
static vec3 cameraFront    = { 0.0f, 0.0f, -1.0f };
static vec3 cameraUp       = { 0.0f, 1.0f,  0.0f };

void cameraInit(void) {
	camera.speed =   6.0f;
	camera.fov   =  45.0f;
	camera.yaw   = -90.0f;
	camera.pitch =   0.0f;
	glm_vec3_copy(cameraPosition, camera.position);
	glm_vec3_copy(cameraFront, camera.front);
	glm_vec3_copy(cameraUp, camera.up);
}

void cameraUpdate(void) {

	f32 scaledSpeed = camera.speed * time.delta;

	camera.forward[0] = cosf(glm_rad(camera.yaw));
	camera.forward[1] = 0.0f;
	camera.forward[2] = sinf(glm_rad(camera.yaw));
	glm_vec3_scale(camera.forward, scaledSpeed, camera.forward);

	glm_cross(camera.front, camera.up, camera.right);
	glm_normalize(camera.right);
	glm_vec3_scale(camera.right, scaledSpeed, camera.right);

	vec3 scaledUp;
	glm_vec3_scale(camera.up, scaledSpeed, scaledUp);

	if (input.key[INPUT_KEY_FORWARD] == KS_PRESSED || input.key[INPUT_KEY_FORWARD] == KS_HELD) {
		glm_vec3_add(camera.position, camera.forward, camera.position);
	}

	if (input.key[INPUT_KEY_BACKWARD] == KS_PRESSED || input.key[INPUT_KEY_BACKWARD] == KS_HELD) {
		glm_vec3_sub(camera.position, camera.forward, camera.position);
	}

	if (input.key[INPUT_KEY_LEFT] == KS_PRESSED || input.key[INPUT_KEY_LEFT] == KS_HELD) {
		glm_vec3_sub(camera.position, camera.right, camera.position);
	}

	if (input.key[INPUT_KEY_RIGHT] == KS_PRESSED || input.key[INPUT_KEY_RIGHT] == KS_HELD) {
		glm_vec3_add(camera.position, camera.right, camera.position);
	}
	
	if (input.key[INPUT_KEY_DOWN] == KS_PRESSED || input.key[INPUT_KEY_DOWN] == KS_HELD) {
		glm_vec3_sub(camera.position, scaledUp, camera.position);
	}

	if (input.key[INPUT_KEY_UP] == KS_PRESSED || input.key[INPUT_KEY_UP] == KS_HELD) {
		glm_vec3_add(camera.position, scaledUp, camera.position);
	}
}

